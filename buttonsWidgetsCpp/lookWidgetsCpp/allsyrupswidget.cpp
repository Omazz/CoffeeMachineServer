#include "buttonsWidgetsHeader/lookWidgetsHeader/allsyrupswidget.h"
#include "ui_allsyrupswidget.h"

AllSyrupsWidget::AllSyrupsWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSyrupsWidget)
{
    ui->setupUi(this);
    table = new QTableWidget(this);
    ui->verticalLayout->insertWidget(0, table);
}

void AllSyrupsWidget::updateTable(QMap<QString, uint> syrups) {
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(syrups.size());
    QStringList headers = {"Syrup", "Price"};
    table->setHorizontalHeaderLabels(headers);
    QTableWidgetItem* item;
    uint counter = 0;
    for(auto syrup: syrups.keys()) {
        item = new QTableWidgetItem(syrup);
        table->setItem(counter, 0, item);
        item = new QTableWidgetItem(QString::number(syrups[syrup]));
        table->setItem(counter, 1, item);
        counter++;
    }
}


AllSyrupsWidget::~AllSyrupsWidget()
{
    delete ui;
}

void AllSyrupsWidget::on_updateButton_clicked()
{
    emit updateSyrupsTableSignal();
}

