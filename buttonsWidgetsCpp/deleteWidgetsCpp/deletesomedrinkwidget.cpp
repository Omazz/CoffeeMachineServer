#include "buttonsWidgetsHeader/deleteWidgetsHeader/deletesomedrinkwidget.h"
#include "ui_deletesomedrinkwidget.h"

DeleteSomeDrinkWidget::DeleteSomeDrinkWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::DeleteSomeDrinkWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

}

DeleteSomeDrinkWidget::~DeleteSomeDrinkWidget()
{
    delete _ui;
}

void DeleteSomeDrinkWidget::on_pushButton_clicked()
{
    QString drink = _ui->drinkLine->text();
    emit deleteSomeDrinkSignal(drink);
    this->close();
    _ui->drinkLine->clear();
}

