#include "newdrinkwidget.h"
#include "ui_newdrinkwidget.h"

NewDrinkWidget::NewDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDrinkWidget)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

NewDrinkWidget::~NewDrinkWidget()
{
    delete ui;
}

void NewDrinkWidget::on_sendToDatabaseButton_clicked()
{
    QString drink = ui->drinkLine->text();
    QString price = ui->priceLine->text();
    QString number = ui->numberLine->text();
    emit newDrinkSignal(drink, price, number);

    ui->drinkLine->clear();
    ui->priceLine->clear();
    ui->numberLine->clear();
    this->close();
}

