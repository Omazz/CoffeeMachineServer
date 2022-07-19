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
    , ui(new Ui::CoffeeMachine)
{
    ui->setupUi(this);

    socket = new QUdpSocket(this);
    socket->bind(TO_LISTEN_IP, TO_LISTEN_PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagram()));
    dataBase = QSqlDatabase::addDatabase(DATABASE_DRIVER); // driver
    dataBase.setDatabaseName(DATABASE_NAME);
    dataBase.setUserName(DATABASE_USERNAME);
    dataBase.setPassword(DATABASE_PASSWORD);
    dataBase.setPort(DATABASE_PORT);

    initializationDrinksAndSyrups();

    newDrinkWidget = new NewDrinkWidget(this);
    newSyrupWidget = new NewSyrupWidget(this);
    changePriceDrinkWidget = new ChangePriceDrinkWidget(this);
    changePriceSyrupWidget = new ChangePriceSyrupWidget(this);
    deleteSomeDrinkWidget = new DeleteSomeDrinkWidget(this);
    deleteSomeSyrupWidget = new DeleteSomeSyrupWidget(this);
    allDrinksWidget = new AllDrinksWidget(this);
    allSyrupsWidget = new AllSyrupsWidget(this);

    connect(newDrinkWidget, &NewDrinkWidget::newDrinkSignal, this, &CoffeeMachine::addNewDrink);
    connect(newSyrupWidget, &NewSyrupWidget::newSyrupSignal, this, &CoffeeMachine::addNewSyrup);
    connect(changePriceDrinkWidget, &ChangePriceDrinkWidget::changePriceDrinkSignal, this, &CoffeeMachine::changePriceDrink);
    connect(changePriceSyrupWidget, &ChangePriceSyrupWidget::changePriceSyrupSignal, this, &CoffeeMachine::changePriceSyrup);
    connect(deleteSomeDrinkWidget, &DeleteSomeDrinkWidget::deleteSomeDrinkSignal, this, &CoffeeMachine::deleteSomeDrink);
    connect(deleteSomeSyrupWidget, &DeleteSomeSyrupWidget::deleteSomeSyrupSignal, this, &CoffeeMachine::deleteSomeSyrup);
    connect(allDrinksWidget, &AllDrinksWidget::updateDrinksTableSignal, this, &CoffeeMachine::updateDrinksTable);
    connect(allSyrupsWidget, &AllSyrupsWidget::updateSyrupsTableSignal, this, &CoffeeMachine::updateSyrupsTable);
}

void CoffeeMachine:: initializationDrinksAndSyrups()
{
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "SELECT * FROM " + DATABASE_DRINKS_TABLE + ";";
        query->prepare(command);
        query->exec();
        while(query->next()) {
            drinks.append(Drink(query->value(1).toString(), query->value(2).toUInt(), query->value(3).toUInt()));
        }
        command = "SELECT * FROM " + DATABASE_SYRUPS_TABLE + ";";
        query->prepare(command);
        query->exec();
        while(query->next()) {
            syrups.append(Syrup(query->value(1).toString(), query->value(2).toUInt()));
        }
    }
}


void CoffeeMachine:: readDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    QString data;
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        data = datagram.data();
        QStringList stringList = data.split(";");

        QString lastRequest = stringList.at(0);
        Drink drink = findDrink(stringList.at(1));
        bool sugarIsNeeded = stringList.at(2) == "1" ? true : false;
        bool milkIsNeeded = stringList.at(3) == "1" ? true : false;
        bool cinnamonIsNeeded = stringList.at(4) == "1" ? true : false;
        Syrup syrup = findSyrup(stringList.at(5));
        currentOrder.setOrder(drink, sugarIsNeeded, milkIsNeeded, cinnamonIsNeeded, syrup);

        ui->lastRequestLabel->setText(data);
        if(lastRequest == BUY_COMMAND_HEADER) {
            writeDatagram(lastRequest + ";" + (haveInStock() ? BUY_SUCCESS_COMMAND : BUY_FAILURE_COMMAND));
        } else if(lastRequest == CHECK_COMMAND_HEADER) {
            writeDatagram(lastRequest + ";" + QString::number(calculatePriceOrder()));
        }
    }
}

quint16 CoffeeMachine:: calculatePriceOrder() {
    int priceDrink = currentOrder.getDrink().getPrice();
    int priceSugar = (currentOrder.isNeededSugar() ? priceOfSugar : 0);
    int priceMilk = (currentOrder.isNeededMilk() ? priceOfMilk : 0);
    int priceCinnamon = (currentOrder.isNeededCinnamon() ? priceOfCinnamon : 0);
    int priceSyrup = currentOrder.getSyrup().getPrice();

    return priceDrink + priceSugar + priceMilk + priceCinnamon + priceSyrup;
}


void CoffeeMachine:: writeDatagram(QString data)
{
    socket->writeDatagram(data.toUtf8(), TO_SEND_IP, TO_SEND_PORT);
}

bool CoffeeMachine:: haveInStock() {
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "SELECT " + DATABASE_AMOUNT_DRINK_FIELD + " FROM " + DATABASE_DRINKS_TABLE
                + " WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink ;";
        query->prepare(command);
        query->bindValue(":drink", currentOrder.getDrink().getName());
        query->exec();
        query->next();
        quint16 number = query->value(0).toInt();
        if(number > 1) {
            command = "UPDATE " + DATABASE_DRINKS_TABLE +
                    " SET " + DATABASE_AMOUNT_DRINK_FIELD + " = :number "+
                    "WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink;";
            query->prepare(command);
            query->bindValue(":number", QString::number(number - 1));
            query->bindValue(":drink", currentOrder.getDrink().getName());
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
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "INSERT INTO " + DATABASE_ORDERS_TABLE +
                " (drink, syrup, sugar, milk, cinnamon, price, correct, date) "
                "VALUES (:drink, :syrup, :sugar, :milk, :cinnamon, :price, :correct, :date);";
        query->prepare(command);
        query->bindValue(":drink", currentOrder.getDrink().getName());
        query->bindValue(":syrup", currentOrder.getSyrup().getName());
        query->bindValue(":sugar", currentOrder.isNeededSugar());
        query->bindValue(":milk", currentOrder.isNeededMilk());
        query->bindValue(":cinnamon", currentOrder.isNeededCinnamon());
        query->bindValue(":price", calculatePriceOrder());
        query->bindValue(":correct", isCorrect);
        query->bindValue(":date", QDateTime::currentDateTime());
        query->exec();
    }
}

void CoffeeMachine::updateDrinks() {
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "SELECT * FROM " + DATABASE_DRINKS_TABLE + ";";
        query->prepare(command);
        query->exec();
        drinks.clear();
        while(query->next()) {
            drinks.append(Drink(query->value(1).toString(), query->value(2).toUInt(), query->value(3).toUInt()));
        }
    }
}

void CoffeeMachine::updateSyrups() {
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "SELECT * FROM " + DATABASE_SYRUPS_TABLE + ";";
        query->prepare(command);
        query->exec();
        syrups.clear();
        while(query->next()) {
            syrups.append(Syrup(query->value(1).toString(), query->value(2).toUInt()));
        }
    }
}

CoffeeMachine::~CoffeeMachine()
{
    delete ui;
}

void CoffeeMachine::addNewDrink(QString drink, QString price, QString number) {
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
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
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
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
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
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
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
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
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "DELETE FROM " + DATABASE_DRINKS_TABLE +
                " WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink";
        query->prepare(command);
        query->bindValue(":drink", drink);
        query->exec();
    }
}

void CoffeeMachine::deleteSomeSyrup(QString syrup) {
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "DELETE FROM " + DATABASE_SYRUPS_TABLE +
                " WHERE " + DATABASE_SYRUP_NAME_FIELD + " = :syrup";
        query->prepare(command);
        query->bindValue(":syrup", syrup);
        query->exec();
    }
}

void CoffeeMachine::updateDrinksTable() {
    updateDrinks();
    allDrinksWidget->updateTable(drinks);
}

void CoffeeMachine::updateSyrupsTable() {
    updateSyrups();
    allSyrupsWidget->updateTable(syrups);
}

Drink CoffeeMachine::findDrink(QString nameDrink) {
    for(uint counter = 0; counter < drinks.size(); ++counter) {
        if(drinks[counter].getName() == nameDrink) {
            return drinks[counter];
        }
    }
    throw new QException;
}

Syrup CoffeeMachine::findSyrup(QString nameSyrup) {
    for(uint counter = 0; counter < syrups.size(); ++counter) {
        if(syrups[counter].getName() == nameSyrup) {
            return syrups[counter];
        }
    }
    throw new QException;
}

void CoffeeMachine::on_addNewDrinkButton_clicked()
{
    newDrinkWidget->setModal(true);
    newDrinkWidget->show();
}


void CoffeeMachine::on_addNewSyrupButton_clicked()
{
    newSyrupWidget->setModal(true);
    newSyrupWidget->show();
}


void CoffeeMachine::on_changePriceDrinksButton_clicked()
{
    changePriceDrinkWidget->setModal(true);
    changePriceDrinkWidget->show();
}


void CoffeeMachine::on_changePriceSyrupsButton_clicked()
{
    changePriceSyrupWidget->setModal(true);
    changePriceSyrupWidget->show();
}


void CoffeeMachine::on_deleteSomeDrinkButton_clicked()
{
    deleteSomeDrinkWidget->setModal(true);
    deleteSomeDrinkWidget->show();
}


void CoffeeMachine::on_deleteSomeSyrupButton_clicked()
{
    deleteSomeSyrupWidget->setModal(true);
    deleteSomeSyrupWidget->show();
}


void CoffeeMachine::on_allDrinksButton_clicked()
{
    allDrinksWidget->setModal(true);
    allDrinksWidget->updateTable(drinks);
    allDrinksWidget->show();
}


void CoffeeMachine::on_allSyrupsButton_clicked()
{
    allSyrupsWidget->setModal(true);
    allSyrupsWidget->updateTable(syrups);
    allSyrupsWidget->show();
}

