#include "newdrinkwidget.h"
#include "ui_newdrinkwidget.h"

newDrinkWidget::newDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDrinkWidget)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height())
}

newDrinkWidget::~newDrinkWidget()
{
    delete ui;
}

void newDrinkWidget::on_sendToDatabaseButton_clicked()
{
    QString drink = ui->drinkLine->text();
    QString price = ui->priceLine->text();
    QString number = ui->numberLine->text();
    // послать сигнал
    this->close();
}

