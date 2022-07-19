#include "coffeemachine.h"
#include "ui_coffeemachine.h"

const QString CoffeeMachine:: BUY_COMMAND_HEADER = "BUY";
const QString CoffeeMachine:: CHECK_COMMAND_HEADER = "CHECK";
const QString CoffeeMachine:: BUY_SUCCESS_COMMAND = "SUCCESS";
const QString CoffeeMachine:: BUY_FAILURE_COMMAND = "FAILURE";
const QString CoffeeMachine:: DATABASE_DRIVER = "QPSQL";
const QString CoffeeMachine:: DATABASE_NAME = "coffeeMachineDataBase";
const QString CoffeeMachine:: DATABASE_USERNAME = "postgres";
const QString CoffeeMachine:: DATABASE_PASSWORD = "root";
const QString CoffeeMachine:: DATABASE_DRINKS_TABLE = "\"drinksTable\"";
const QString CoffeeMachine:: DATABASE_DRINK_NAME_FIELD = "\"drink\"";
const QString CoffeeMachine:: DATABASE_SYRUP_NAME_FIELD = "\"syrup\"";
const QString CoffeeMachine:: DATABASE_AMOUNT_DRINK_FIELD = "\"number\"";
const QString CoffeeMachine:: DATABASE_PRICE_FIELD = "\"price\"";
const QString CoffeeMachine:: DATABASE_SYRUPS_TABLE = "\"syrupsTable\"";
const QString CoffeeMachine:: DATABASE_ORDERS_TABLE = "\"ordersTable\"";

CoffeeMachine::CoffeeMachine(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::CoffeeMachine)
{
    _ui->setupUi(this);

    _socket = new QUdpSocket(this);
    _socket->bind(TO_LISTEN_IP, TO_LISTEN_PORT);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readDatagram()));

    _dataBase = QSqlDatabase::addDatabase(DATABASE_DRIVER); // driver
    _dataBase.setDatabaseName(DATABASE_NAME);
    _dataBase.setUserName(DATABASE_USERNAME);
    _dataBase.setPassword(DATABASE_PASSWORD);
    _dataBase.setPort(DATABASE_PORT);

    initializationDrinksAndSyrups();

    _newDrinkWidget = new NewDrinkWidget(this);
    _newSyrupWidget = new NewSyrupWidget(this);
    _changePriceDrinkWidget = new ChangePriceDrinkWidget(this);
    _changePriceSyrupWidget = new ChangePriceSyrupWidget(this);
    _deleteSomeDrinkWidget = new DeleteSomeDrinkWidget(this);
    _deleteSomeSyrupWidget = new DeleteSomeSyrupWidget(this);
    _allDrinksWidget = new AllDrinksWidget(this);
    _allSyrupsWidget = new AllSyrupsWidget(this);

    connect(_newDrinkWidget, &NewDrinkWidget::newDrinkSignal, this, &CoffeeMachine::addNewDrink);
    connect(_newSyrupWidget, &NewSyrupWidget::newSyrupSignal, this, &CoffeeMachine::addNewSyrup);
    connect(_changePriceDrinkWidget, &ChangePriceDrinkWidget::changePriceDrinkSignal, this, &CoffeeMachine::changePriceDrink);
    connect(_changePriceSyrupWidget, &ChangePriceSyrupWidget::changePriceSyrupSignal, this, &CoffeeMachine::changePriceSyrup);
    connect(_deleteSomeDrinkWidget, &DeleteSomeDrinkWidget::deleteSomeDrinkSignal, this, &CoffeeMachine::deleteSomeDrink);
    connect(_deleteSomeSyrupWidget, &DeleteSomeSyrupWidget::deleteSomeSyrupSignal, this, &CoffeeMachine::deleteSomeSyrup);
    connect(_allDrinksWidget, &AllDrinksWidget::updateDrinksTableSignal, this, &CoffeeMachine::updateDrinksTable);
    connect(_allSyrupsWidget, &AllSyrupsWidget::updateSyrupsTableSignal, this, &CoffeeMachine::updateSyrupsTable);
}

void CoffeeMachine:: initializationDrinksAndSyrups()
{
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "SELECT * FROM " + DATABASE_DRINKS_TABLE + ";";
        query->prepare(command);
        query->exec();
        while(query->next()) {
            _drinks.append(Drink(query->value(1).toString(), query->value(2).toUInt(), query->value(3).toUInt()));
        }
        command = "SELECT * FROM " + DATABASE_SYRUPS_TABLE + ";";
        query->prepare(command);
        query->exec();
        while(query->next()) {
            _syrups.append(Syrup(query->value(1).toString(), query->value(2).toUInt()));
        }
    }
}


void CoffeeMachine:: readDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    QString data;
    while (_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_socket->pendingDatagramSize());
        _socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        data = datagram.data();
        QStringList stringList = data.split(";");

        QString lastRequest = stringList.at(0);
        Drink drink = findDrink(stringList.at(1));
        bool sugarIsNeeded = stringList.at(2) == "1" ? true : false;
        bool milkIsNeeded = stringList.at(3) == "1" ? true : false;
        bool cinnamonIsNeeded = stringList.at(4) == "1" ? true : false;
        Syrup syrup = findSyrup(stringList.at(5));
        _currentOrder.setOrder(drink, sugarIsNeeded, milkIsNeeded, cinnamonIsNeeded, syrup);

        _ui->lastRequestLabel->setText(data);
        if(lastRequest == BUY_COMMAND_HEADER) {
            writeDatagram(lastRequest + ";" + (haveInStock() ? BUY_SUCCESS_COMMAND : BUY_FAILURE_COMMAND));
        } else if(lastRequest == CHECK_COMMAND_HEADER) {
            writeDatagram(lastRequest + ";" + QString::number(calculatePriceOrder()));
        }
    }
}

quint16 CoffeeMachine:: calculatePriceOrder() {
    int priceDrink = _currentOrder.getDrink().getPrice();
    int priceSugar = (_currentOrder.isNeededSugar() ? priceOfSugar : 0);
    int priceMilk = (_currentOrder.isNeededMilk() ? priceOfMilk : 0);
    int priceCinnamon = (_currentOrder.isNeededCinnamon() ? priceOfCinnamon : 0);
    int priceSyrup = _currentOrder.getSyrup().getPrice();

    return priceDrink + priceSugar + priceMilk + priceCinnamon + priceSyrup;
}


void CoffeeMachine:: writeDatagram(QString data)
{
    _socket->writeDatagram(data.toUtf8(), TO_SEND_IP, TO_SEND_PORT);
}

bool CoffeeMachine:: haveInStock() {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "SELECT " + DATABASE_AMOUNT_DRINK_FIELD + " FROM " + DATABASE_DRINKS_TABLE
                + " WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink ;";
        query->prepare(command);
        query->bindValue(":drink", _currentOrder.getDrink().getName());
        query->exec();
        query->next();
        uint number = query->value(0).toUInt();
        if(number > 1) {
            command = "UPDATE " + DATABASE_DRINKS_TABLE +
                    " SET " + DATABASE_AMOUNT_DRINK_FIELD + " = :number "+
                    "WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink;";
            query->prepare(command);
            query->bindValue(":number", QString::number(number - 1));
            query->bindValue(":drink", _currentOrder.getDrink().getName());
            query->exec();
            updateOrdersLogs(true);
            return true;
        } else {
            updateOrdersLogs(false);
        }
        return false;
    } else {
        qDebug() << "data base is not openned";
    }
    return false;
}

void CoffeeMachine:: updateOrdersLogs(bool isCorrect) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "INSERT INTO " + DATABASE_ORDERS_TABLE +
                " (drink, syrup, sugar, milk, cinnamon, price, correct, date) "
                "VALUES (:drink, :syrup, :sugar, :milk, :cinnamon, :price, :correct, :date);";
        query->prepare(command);
        query->bindValue(":drink", _currentOrder.getDrink().getName());
        query->bindValue(":syrup", _currentOrder.getSyrup().getName());
        query->bindValue(":sugar", _currentOrder.isNeededSugar());
        query->bindValue(":milk", _currentOrder.isNeededMilk());
        query->bindValue(":cinnamon", _currentOrder.isNeededCinnamon());
        query->bindValue(":price", calculatePriceOrder());
        query->bindValue(":correct", isCorrect);
        query->bindValue(":date", QDateTime::currentDateTime());
        query->exec();
    }
}

void CoffeeMachine::updateDrinks() {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "SELECT * FROM " + DATABASE_DRINKS_TABLE + ";";
        query->prepare(command);
        query->exec();
        _drinks.clear();
        while(query->next()) {
            _drinks.append(Drink(query->value(1).toString(), query->value(2).toUInt(), query->value(3).toUInt()));
        }
    }
}

void CoffeeMachine::updateSyrups() {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "SELECT * FROM " + DATABASE_SYRUPS_TABLE + ";";
        query->prepare(command);
        query->exec();
        _syrups.clear();
        while(query->next()) {
            _syrups.append(Syrup(query->value(1).toString(), query->value(2).toUInt()));
        }
    }
}

CoffeeMachine::~CoffeeMachine()
{
    delete _ui;
}

void CoffeeMachine::addNewDrink(QString drink, QString price, QString number) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "INSERT INTO " + DATABASE_DRINKS_TABLE +
                " (drink, price, number) "
                "VALUES (:drink, :price, :number);";
        query->prepare(command);
        query->bindValue(":drink", drink);
        query->bindValue(":price", price.toUInt());
        query->bindValue(":number", number.toUInt());
        query->exec();
    }
}
void CoffeeMachine::addNewSyrup(QString syrup, QString price) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "INSERT INTO" + DATABASE_SYRUPS_TABLE +
                " (syrup, price) "
                "VALUES (:syrup, :price);";
        query->prepare(command);
        query->bindValue(":syrup", syrup);
        query->bindValue(":price", price.toUInt());
        query->exec();
    }
}

void CoffeeMachine::changePriceDrink(QString drink, QString price) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "UPDATE " + DATABASE_DRINKS_TABLE +
                " SET " + DATABASE_PRICE_FIELD + " = :price" +
                " WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink";
        query->prepare(command);
        query->bindValue(":price", price.toUInt());
        query->bindValue(":drink", drink);
        query->exec();
    }
}

void CoffeeMachine::changePriceSyrup(QString syrup, QString price) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "UPDATE " + DATABASE_SYRUPS_TABLE +
                " SET " + DATABASE_PRICE_FIELD + " = :price" +
                " WHERE " + DATABASE_SYRUP_NAME_FIELD + " = :syrup";
        query->prepare(command);
        query->bindValue(":price", price.toUInt());
        query->bindValue(":syrup", syrup);
        query->exec();
    }
}

void CoffeeMachine::deleteSomeDrink(QString drink) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "DELETE FROM " + DATABASE_DRINKS_TABLE +
                " WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink";
        query->prepare(command);
        query->bindValue(":drink", drink);
        query->exec();
    }
}

void CoffeeMachine::deleteSomeSyrup(QString syrup) {
    if(_dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(_dataBase);
        QString command = "DELETE FROM " + DATABASE_SYRUPS_TABLE +
                " WHERE " + DATABASE_SYRUP_NAME_FIELD + " = :syrup";
        query->prepare(command);
        query->bindValue(":syrup", syrup);
        query->exec();
    }
}

void CoffeeMachine::updateDrinksTable() {
    updateDrinks();
    _allDrinksWidget->updateTable(_drinks);
}

void CoffeeMachine::updateSyrupsTable() {
    updateSyrups();
    _allSyrupsWidget->updateTable(_syrups);
}

Drink CoffeeMachine::findDrink(QString nameDrink) {
    for(uint counter = 0; counter < _drinks.size(); ++counter) {
        if(_drinks[counter].getName() == nameDrink) {
            return _drinks[counter];
        }
    }
    throw new QException;
}

Syrup CoffeeMachine::findSyrup(QString nameSyrup) {
    for(uint counter = 0; counter < _syrups.size(); ++counter) {
        if(_syrups[counter].getName() == nameSyrup) {
            return _syrups[counter];
        }
    }
    throw new QException;
}

void CoffeeMachine::on_addNewDrinkButton_clicked()
{
    _newDrinkWidget->setModal(true);
    _newDrinkWidget->show();
}


void CoffeeMachine::on_addNewSyrupButton_clicked()
{
    _newSyrupWidget->setModal(true);
    _newSyrupWidget->show();
}


void CoffeeMachine::on_changePriceDrinksButton_clicked()
{
    _changePriceDrinkWidget->setModal(true);
    _changePriceDrinkWidget->show();
}


void CoffeeMachine::on_changePriceSyrupsButton_clicked()
{
    _changePriceSyrupWidget->setModal(true);
    _changePriceSyrupWidget->show();
}


void CoffeeMachine::on_deleteSomeDrinkButton_clicked()
{
    _deleteSomeDrinkWidget->setModal(true);
    _deleteSomeDrinkWidget->show();
}


void CoffeeMachine::on_deleteSomeSyrupButton_clicked()
{
    _deleteSomeSyrupWidget->setModal(true);
    _deleteSomeSyrupWidget->show();
}


void CoffeeMachine::on_allDrinksButton_clicked()
{
    _allDrinksWidget->setModal(true);
    _allDrinksWidget->updateTable(_drinks);
    _allDrinksWidget->show();
}


void CoffeeMachine::on_allSyrupsButton_clicked()
{
    _allSyrupsWidget->setModal(true);
    _allSyrupsWidget->updateTable(_syrups);
    _allSyrupsWidget->show();
}

