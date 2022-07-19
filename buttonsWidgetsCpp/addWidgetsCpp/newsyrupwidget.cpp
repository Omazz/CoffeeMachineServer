#include "buttonsWidgetsHeader/addWidgetsHeader/newsyrupwidget.h"
#include "ui_newsyrupwidget.h"

NewSyrupWidget::NewSyrupWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSyrupWidget)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

NewSyrupWidget::~NewSyrupWidget()
{
    delete ui;
}

void NewSyrupWidget::on_sendToDatabaseButton_clicked()
{
    QString syrup = ui->syrupLine->text();
    QString price = ui->priceLine->text();
    emit newSyrupSignal(syrup, price);
    ui->syrupLine->clear();
    ui->priceLine->clear();
    this->close();
}

