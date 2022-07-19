#include "buttonsWidgetsHeader/changeWidgetsHeader/changepricesyrupwidget.h"
#include "ui_changepricesyrupwidget.h"

ChangePriceSyrupWidget::ChangePriceSyrupWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::ChangePriceSyrupWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

}

ChangePriceSyrupWidget::~ChangePriceSyrupWidget()
{
    delete _ui;
}

void ChangePriceSyrupWidget::on_pushButton_clicked()
{
    QString syrup = _ui->syrupLine->text();
    QString price = _ui->priceLine->text();
    emit changePriceSyrupSignal(syrup, price);
    this->close();
    _ui->syrupLine->clear();
    _ui->priceLine->clear();
}

