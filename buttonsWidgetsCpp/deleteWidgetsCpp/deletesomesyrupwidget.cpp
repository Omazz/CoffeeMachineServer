#include "deletesomesyrupwidget.h"
#include "ui_deletesomesyrupwidget.h"

DeleteSomeSyrupWidget::DeleteSomeSyrupWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteSomeSyrupWidget)
{
    ui->setupUi(this);
}

DeleteSomeSyrupWidget::~DeleteSomeSyrupWidget()
{
    delete ui;
}

void DeleteSomeSyrupWidget::on_pushButton_clicked()
{
    QString syrup = ui->syrupLine->text();
    emit deleteSomeSyrupSignal(syrup);
    this->close();
    ui->syrupLine->clear();
}

