#include "buttonsWidgetsHeader/lookWidgetsHeader/alldrinkswidget.h"
#include "ui_alldrinkswidget.h"

AllDrinksWidget::AllDrinksWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllDrinksWidget)
{
    ui->setupUi(this);
}

AllDrinksWidget::~AllDrinksWidget()
{
    delete ui;
}
