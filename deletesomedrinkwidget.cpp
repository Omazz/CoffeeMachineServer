#include "deletesomedrinkwidget.h"
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
