#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#include "order.h"
#include <QMainWindow>
#include <QUdpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class CoffeeMachine; }
QT_END_NAMESPACE

class CoffeeMachine : public QMainWindow
{
    Q_OBJECT

public:
    CoffeeMachine(QWidget *parent = nullptr);
    ~CoffeeMachine();
public slots:
    void readDatagram();
private:
    void initPrices();
    quint16 calculatePriceOrder();
    void writeDatagram(QString data);
    bool haveInStock();
    void updateOrdersLogs(bool isCorrect);

    Ui::CoffeeMachine *ui;
    Order currentOrder;

    QSqlDatabase dataBase;
    QMap<QString, int> pricesOfDrinks;
    QMap<QString, int> pricesOfSyrups;
    const static int priceOfSugar = 10;
    const static int priceOfMilk = 30;
    const static int priceOfCinnamon = 20;

    const static QString DATABASE_DRIVER;
    const static QString DATABASE_NAME;
    const static QString DATABASE_USERNAME;
    const static QString DATABASE_PASSWORD;
    const static quint16 DATABASE_PORT = 5433;

    const static QString DATABASE_DRINKS_TABLE;
    const static QString DATABASE_SYRUPS_TABLE;
    const static QString DATABASE_ORDERS_TABLE;

    const static QString DATABASE_DRINK_NAME_FIELD;
    const static QString DATABASE_AMOUNT_DRINK_FIELD;

    QUdpSocket* socket;
    const static QString BUY_COMMAND_HEADER;
    const static QString CHECK_COMMAND_HEADER;
    const static QString BUY_SUCCESS_COMMAND;
    const static QString BUY_FAILURE_COMMAND;
    const static QString BUY__COMMAND;
    const static quint16 TO_LISTEN_PORT = 8090; // порт на котором мы будем слушать чужие сообщения
    const static QHostAddress::SpecialAddress TO_LISTEN_IP = QHostAddress::LocalHost; // айпи на котором мы будем слушать чужие сообщения
    const static quint16 TO_SEND_PORT = 8080; // порт на который мы будем отправлять наши сообщения
    const static QHostAddress::SpecialAddress TO_SEND_IP = QHostAddress::LocalHost; // айпи на которое мы будем отправлять наши сообщения
};
#endif // COFFEEMACHINE_H
