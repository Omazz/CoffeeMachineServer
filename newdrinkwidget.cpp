#include "newdrinkwidget.h"
#include "ui_newdrinkwidget.h"

newDrinkWidget::newDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDrinkWidget)
{
    ui->setupUi(this);
}

newDrinkWidget::~newDrinkWidget()
{
    delete ui;
}
