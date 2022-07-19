#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#include "order.h"
#include "drink.h"
#include "syrup.h"
#include "buttonsWidgetsHeader/addWidgetsHeader/newdrinkwidget.h"
#include "buttonsWidgetsHeader/addWidgetsHeader/newsyrupwidget.h"
#include "buttonsWidgetsHeader/changeWidgetsHeader/changepricedrinkwidget.h"
#include "buttonsWidgetsHeader/changeWidgetsHeader/changepricesyrupwidget.h"
#include "buttonsWidgetsHeader/deleteWidgetsHeader/deletesomedrinkwidget.h"
#include "buttonsWidgetsHeader/deleteWidgetsHeader/deletesomesyrupwidget.h"
#include "buttonsWidgetsHeader/lookWidgetsHeader/alldrinkswidget.h"
#include "buttonsWidgetsHeader/lookWidgetsHeader/allsyrupswidget.h"

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
    const static QString DATABASE_SYRUP_NAME_FIELD;
    const static QString DATABASE_AMOUNT_DRINK_FIELD;
    const static QString DATABASE_PRICE_FIELD;

    const static QString BUY_COMMAND_HEADER;
    const static QString CHECK_COMMAND_HEADER;
    const static QString BUY_SUCCESS_COMMAND;
    const static QString BUY_FAILURE_COMMAND;
    const static QString BUY_COMMAND;
    const static quint16 TO_LISTEN_PORT = 8090; // порт на котором мы будем слушать чужие сообщения
    const static QHostAddress::SpecialAddress TO_LISTEN_IP = QHostAddress::LocalHost; // айпи на котором мы будем слушать чужие сообщения
    const static quint16 TO_SEND_PORT = 8080; // порт на который мы будем отправлять наши сообщения
    const static QHostAddress::SpecialAddress TO_SEND_IP = QHostAddress::LocalHost; // айпи на которое мы будем отправлять наши сообщения


    CoffeeMachine(QWidget *parent = nullptr);
    ~CoffeeMachine();

public slots:
    void readDatagram();

private slots:
    void addNewDrink(QString drink, QString price, QString number);
    void addNewSyrup(QString syrup, QString price);
    void changePriceDrink(QString drink, QString price);
    void changePriceSyrup(QString syrup, QString price);
    void deleteSomeDrink(QString drink);
    void deleteSomeSyrup(QString syrup);
    void updateDrinksTable();
    void updateSyrupsTable();

    void on_addNewDrinkButton_clicked();
    void on_addNewSyrupButton_clicked();
    void on_changePriceDrinksButton_clicked();
    void on_changePriceSyrupsButton_clicked();
    void on_deleteSomeDrinkButton_clicked();
    void on_deleteSomeSyrupButton_clicked();
    void on_allDrinksButton_clicked();
    void on_allSyrupsButton_clicked();

private:
    void initPrices();
    quint16 calculatePriceOrder();
    void writeDatagram(QString data);
    bool haveInStock();
    void updateOrdersLogs(bool isCorrect);
    void updateDrinks();
    void updateSyrups();

    Ui::CoffeeMachine *ui;
    Order currentOrder;

    QSqlDatabase dataBase;
    QMap<QString, uint> pricesOfDrinks;
    QMap<QString, uint> pricesOfSyrups;

    NewDrinkWidget* newDrinkWidget;
    NewSyrupWidget* newSyrupWidget;
    ChangePriceDrinkWidget* changePriceDrinkWidget;
    ChangePriceSyrupWidget* changePriceSyrupWidget;
    DeleteSomeDrinkWidget* deleteSomeDrinkWidget;
    DeleteSomeSyrupWidget* deleteSomeSyrupWidget;
    AllDrinksWidget* allDrinksWidget;
    AllSyrupsWidget* allSyrupsWidget;

    QUdpSocket* socket;
};
#endif // COFFEEMACHINE_H
