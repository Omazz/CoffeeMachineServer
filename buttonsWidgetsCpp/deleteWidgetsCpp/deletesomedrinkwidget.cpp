#include "buttonsWidgetsHeader/deleteWidgetsHeader/deletesomedrinkwidget.h"
#include "ui_deletesomedrinkwidget.h"

DeleteSomeDrinkWidget::DeleteSomeDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteSomeDrinkWidget)
{
    ui->setupUi(this);
}

DeleteSomeDrinkWidget::~DeleteSomeDrinkWidget()
{
    delete ui;
}

void DeleteSomeDrinkWidget::on_pushButton_clicked()
{
    QString drink = ui->drinkLine->text();
    emit deleteSomeDrinkSignal(drink);
    this->close();
    ui->drinkLine->clear();
}

