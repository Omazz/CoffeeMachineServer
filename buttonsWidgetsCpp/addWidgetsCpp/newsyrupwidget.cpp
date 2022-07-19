#include "buttonsWidgetsHeader/addWidgetsHeader/newsyrupwidget.h"
#include "ui_newsyrupwidget.h"

NewSyrupWidget::NewSyrupWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewSyrupWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

NewSyrupWidget::~NewSyrupWidget()
{
    delete _ui;
}

void NewSyrupWidget::on_sendToDatabaseButton_clicked()
{
    QString syrup = _ui->syrupLine->text();
    QString price = _ui->priceLine->text();
    emit newSyrupSignal(syrup, price);
    _ui->syrupLine->clear();
    _ui->priceLine->clear();
    this->close();
}

