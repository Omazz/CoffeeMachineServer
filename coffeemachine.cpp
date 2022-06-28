#include "coffeemachine.h"
#include "ui_coffeemachine.h"
#include <QMessageBox>


const QString CoffeeMachine:: BUY_COMMAND_HEADER = (QString) "BUY";
const QString CoffeeMachine:: CHECK_COMMAND_HEADER = (QString) "CHECK";
const QString CoffeeMachine:: BUY_SUCCESS_COMMAND = (QString) "SUCCESS";
const QString CoffeeMachine:: BUY_FAILURE_COMMAND = (QString) "FAILURE";
const QString CoffeeMachine:: DATABASE_DRIVER = (QString) "QPSQL";
const QString CoffeeMachine:: DATABASE_NAME = (QString) "coffeeMachineDataBase";
const QString CoffeeMachine:: DATABASE_USERNAME = (QString) "postgres";
const QString CoffeeMachine:: DATABASE_PASSWORD = (QString) "root";
const QString CoffeeMachine:: DATABASE_DRINKS_TABLE = "\"drinksTable\"";
const QString CoffeeMachine:: DATABASE_DRINK_NAME_FIELD = "\"drink\"";
const QString CoffeeMachine:: DATABASE_AMOUNT_DRINK_FIELD = "\"number\"";
const QString CoffeeMachine:: DATABASE_SYRUPS_TABLE = "\"syrupsTable\"";


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

    initPrices();
}

void CoffeeMachine:: initPrices()
{
    if(dataBase.open()) {
        QSqlQuery* query = new QSqlQuery(dataBase);
        QString command = "SELECT * FROM " + DATABASE_DRINKS_TABLE + ";";
        query->prepare(command);
        query->exec();
        qDebug() << query->size();
        while(query->next()) {
            pricesOfDrinks.insert(query->value(1).toString(), query->value(2).toInt());
        }
        command = "SELECT * FROM " + DATABASE_SYRUPS_TABLE + ";";
        query->prepare(command);
        query->exec();
        qDebug() << query->size();
        while(query->next()) {
            pricesOfSyrups.insert(query->value(1).toString(), query->value(2).toInt());
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
        QString drink = stringList.at(1);
        bool sugarIsNeeded = stringList.at(2) == "1" ? true : false;
        bool milkIsNeeded = stringList.at(3) == "1" ? true : false;
        bool cinnamonIsNeeded = stringList.at(4) == "1" ? true : false;
        QString syrup = stringList.at(5);
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
    int priceDrink = pricesOfDrinks.find(currentOrder.getDrink()).value();
    int priceSugar = (currentOrder.isNeededSugar() ? priceOfSugar : 0);
    int priceMilk = (currentOrder.isNeededMilk() ? priceOfMilk : 0);
    int priceCinnamon = (currentOrder.isNeededCinnamon() ? priceOfCinnamon : 0);
    int priceSyrup = pricesOfSyrups.find(currentOrder.getSyrup()).value();

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
        query->bindValue(":drink", currentOrder.getDrink());
        query->exec();
        query->next();
        quint16 number = query->value(0).toInt();
        if(number > 1) {
            command = "UPDATE " + DATABASE_DRINKS_TABLE +
                    " SET " + DATABASE_AMOUNT_DRINK_FIELD + " = :number "+
                    "WHERE " + DATABASE_DRINK_NAME_FIELD + " = :drink;";
            qDebug() << query->prepare(command);
            query->bindValue(":number", QString::number(number - 1));
            query->bindValue(":drink", currentOrder.getDrink());
            query->exec();
            return true;
        }
        return false;
    } else {
        qDebug() << "data base is not openned";
    }
    return false;
}

CoffeeMachine::~CoffeeMachine()
{
    delete ui;
}

