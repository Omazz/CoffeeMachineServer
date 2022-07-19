#include "buttonsWidgetsHeader/addWidgetsHeader/newdrinkwidget.h"
#include "ui_newdrinkwidget.h"

NewDrinkWidget::NewDrinkWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewDrinkWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

NewDrinkWidget::~NewDrinkWidget()
{
    delete _ui;
}

void NewDrinkWidget::on_sendToDatabaseButton_clicked()
{
    QString drink = _ui->drinkLine->text();
    QString price = _ui->priceLine->text();
    QString number = _ui->numberLine->text();
    emit newDrinkSignal(drink, price, number);

    _ui->drinkLine->clear();
    _ui->priceLine->clear();
    _ui->numberLine->clear();
    this->close();
}

