#include "buttonsWidgetsHeader/lookWidgetsHeader/allsyrupswidget.h"
#include "ui_allsyrupswidget.h"

AllSyrupsWidget::AllSyrupsWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSyrupsWidget)
{
    ui->setupUi(this);
}

AllSyrupsWidget::~AllSyrupsWidget()
{
    delete ui;
}
