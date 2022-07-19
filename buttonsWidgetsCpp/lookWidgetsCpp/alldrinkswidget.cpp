#include "buttonsWidgetsHeader/lookWidgetsHeader/alldrinkswidget.h"
#include "ui_alldrinkswidget.h"

AllDrinksWidget::AllDrinksWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllDrinksWidget)
{
    ui->setupUi(this);
    table = new QTableWidget(this);
    ui->verticalLayout->insertWidget(0, table);
}

void AllDrinksWidget::updateTable(QVector<Drink> drinks) {
    table->clear();
    table->setColumnCount(3);
    table->setRowCount(drinks.size());
    QStringList headers = {"Drink", "Price", "Number"};
    table->setHorizontalHeaderLabels(headers);
    Drink currentDrink;
    for(uint counter = 0; counter < drinks.size(); ++counter) {
        currentDrink = drinks[counter];
        table->setItem(counter, 0, new QTableWidgetItem(currentDrink.getName()));
        table->setItem(counter, 1, new QTableWidgetItem(QString::number(currentDrink.getPrice())));
        table->setItem(counter, 2, new QTableWidgetItem(QString::number(currentDrink.getNumber())));
    }
}

AllDrinksWidget::~AllDrinksWidget()
{
    delete ui;
}

void AllDrinksWidget::on_updateButton_clicked()
{
    emit updateDrinksTableSignal();
}

