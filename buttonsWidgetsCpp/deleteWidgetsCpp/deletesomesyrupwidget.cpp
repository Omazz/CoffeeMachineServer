#include "buttonsWidgetsHeader/deleteWidgetsHeader/deletesomesyrupwidget.h"
#include "ui_deletesomesyrupwidget.h"

DeleteSomeSyrupWidget::DeleteSomeSyrupWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DeleteSomeSyrupWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

}

DeleteSomeSyrupWidget::~DeleteSomeSyrupWidget()
{
    delete _ui;
}

void DeleteSomeSyrupWidget::on_pushButton_clicked()
{
    QString syrup = _ui->syrupLine->text();
    emit deleteSomeSyrupSignal(syrup);
    this->close();
    _ui->syrupLine->clear();
}

