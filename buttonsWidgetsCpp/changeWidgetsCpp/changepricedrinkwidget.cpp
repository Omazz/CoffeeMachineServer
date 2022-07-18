#include "changepricedrinkwidget.h"
#include "ui_changepricedrinkwidget.h"

ChangePriceDrinkWidget::ChangePriceDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePriceDrinkWidget)
{
    ui->setupUi(this);
}

ChangePriceDrinkWidget::~ChangePriceDrinkWidget()
{
    delete ui;
}

void ChangePriceDrinkWidget::on_pushButton_clicked()
{
    QString drink = ui->drinkLine->text();
    QString price = ui->priceLine->text();
    emit changePriceDrinkSignal(drink, price);
    this->close();
    ui->drinkLine->clear();
    ui->priceLine->clear();
}

