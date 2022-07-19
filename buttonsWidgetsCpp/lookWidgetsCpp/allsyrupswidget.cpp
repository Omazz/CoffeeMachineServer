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

void AllSyrupsWidget::updateTable(QVector<Syrup> syrups) {
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(syrups.size());
    QStringList headers = {"Syrup", "Price"};
    table->setHorizontalHeaderLabels(headers);
    Syrup currentSyrup;
    for(uint counter = 0; counter < syrups.size(); ++counter) {
        currentSyrup = syrups[counter];
        table->setItem(counter, 0, new QTableWidgetItem(currentSyrup.getName()));
        table->setItem(counter, 1, new QTableWidgetItem(QString::number(currentSyrup.getPrice())));
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

