#include "buttonsWidgetsHeader/lookWidgetsHeader/alldrinkswidget.h"
#include "ui_alldrinkswidget.h"

AllDrinksWidget::AllDrinksWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AllDrinksWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    _table = new QTableWidget(this);
    _ui->verticalLayout->insertWidget(0, _table);
}

void AllDrinksWidget::updateTable(QVector<Drink> drinks) {
    _table->clear();
    _table->setColumnCount(3);
    _table->setRowCount(drinks.size());
    QStringList headers = {"Drink", "Price", "Number"};
    _table->setHorizontalHeaderLabels(headers);
    Drink currentDrink;
    for(uint counter = 0; counter < drinks.size(); ++counter) {
        currentDrink = drinks[counter];
        _table->setItem(counter, 0, new QTableWidgetItem(currentDrink.getName()));
        _table->setItem(counter, 1, new QTableWidgetItem(QString::number(currentDrink.getPrice())));
        _table->setItem(counter, 2, new QTableWidgetItem(QString::number(currentDrink.getNumber())));
    }
}

AllDrinksWidget::~AllDrinksWidget()
{
    delete _ui;
}

void AllDrinksWidget::on_updateButton_clicked()
{
    emit updateDrinksTableSignal();
}

