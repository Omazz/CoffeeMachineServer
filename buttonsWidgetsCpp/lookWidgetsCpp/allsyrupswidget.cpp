#include "buttonsWidgetsHeader/lookWidgetsHeader/allsyrupswidget.h"
#include "ui_allsyrupswidget.h"

AllSyrupsWidget::AllSyrupsWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AllSyrupsWidget)
{
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    _table = new QTableWidget(this);
    _ui->verticalLayout->insertWidget(0, _table);
}

void AllSyrupsWidget::updateTable(QVector<Syrup> syrups) {
    _table->clear();
    _table->setColumnCount(2);
    _table->setRowCount(syrups.size());
    QStringList headers = {"Syrup", "Price"};
    _table->setHorizontalHeaderLabels(headers);
    Syrup currentSyrup;
    for(uint counter = 0; counter < syrups.size(); ++counter) {
        currentSyrup = syrups[counter];
        _table->setItem(counter, 0, new QTableWidgetItem(currentSyrup.getName()));
        _table->setItem(counter, 1, new QTableWidgetItem(QString::number(currentSyrup.getPrice())));
    }
}


AllSyrupsWidget::~AllSyrupsWidget()
{
    delete _ui;
}

void AllSyrupsWidget::on_updateButton_clicked()
{
    emit updateSyrupsTableSignal();
}

