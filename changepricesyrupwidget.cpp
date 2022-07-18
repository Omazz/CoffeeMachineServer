#include "changepricesyrupwidget.h"
#include "ui_changepricesyrupwidget.h"

ChangePriceSyrupWidget::ChangePriceSyrupWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePriceSyrupWidget)
{
    ui->setupUi(this);
}

ChangePriceSyrupWidget::~ChangePriceSyrupWidget()
{
    delete ui;
}

void ChangePriceSyrupWidget::on_pushButton_clicked()
{
    QString syrup = ui->syrupLine->text();
    QString price = ui->priceLine->text();
    emit changePriceSyrupSignal(syrup, price);
    this->close();
    ui->syrupLine->clear();
    ui->priceLine->clear();
}

