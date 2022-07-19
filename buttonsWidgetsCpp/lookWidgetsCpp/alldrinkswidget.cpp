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

void AllDrinksWidget::updateTable(QMap<QString,uint> drinks) {
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(drinks.size());
    QStringList headers = {"Drink", "Price"};
    table->setHorizontalHeaderLabels(headers);
    QTableWidgetItem* item;
    uint counter = 0;
    for(auto name: drinks.keys()) {
        item = new QTableWidgetItem(name);
        table->setItem(counter, 0, item);
        item = new QTableWidgetItem(QString::number(drinks[name]));
        table->setItem(counter, 1, item);
        ++counter;
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

