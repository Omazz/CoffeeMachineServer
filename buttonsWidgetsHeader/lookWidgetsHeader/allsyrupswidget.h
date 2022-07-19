#ifndef ALLSYRUPSWIDGET_H
#define ALLSYRUPSWIDGET_H

#include "syrup.h"
#include <QTableWidget>
#include <QDialog>

namespace Ui {
class AllSyrupsWidget;
}

class AllSyrupsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AllSyrupsWidget(QWidget *parent = nullptr);
    void updateTable(QVector<Syrup> syrups);
    ~AllSyrupsWidget();

signals:
    void updateSyrupsTableSignal();

private slots:
    void on_updateButton_clicked();

private:
    QTableWidget* _table;
    Ui::AllSyrupsWidget* _ui;
};

#endif // ALLSYRUPSWIDGET_H
