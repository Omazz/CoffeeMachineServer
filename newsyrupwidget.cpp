#include "newsyrupwidget.h"
#include "ui_newsyrupwidget.h"

newSyrupWidget::newSyrupWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newSyrupWidget)
{
    ui->setupUi(this);
}

newSyrupWidget::~newSyrupWidget()
{
    delete ui;
}
