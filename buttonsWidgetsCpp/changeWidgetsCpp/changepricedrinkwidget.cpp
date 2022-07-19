#include "buttonsWidgetsHeader/changeWidgetsHeader/changepricedrinkwidget.h"
#include "ui_changepricedrinkwidget.h"

ChangePriceDrinkWidget::ChangePriceDrinkWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ChangePriceDrinkWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

}

ChangePriceDrinkWidget::~ChangePriceDrinkWidget()
{
    delete _ui;
}

void ChangePriceDrinkWidget::on_pushButton_clicked()
{
    QString drink = _ui->drinkLine->text();
    QString price = _ui->priceLine->text();
    emit changePriceDrinkSignal(drink, price);
    this->close();
    _ui->drinkLine->clear();
    _ui->priceLine->clear();
}

