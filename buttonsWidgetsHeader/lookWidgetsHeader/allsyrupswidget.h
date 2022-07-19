#ifndef ALLSYRUPSWIDGET_H
#define ALLSYRUPSWIDGET_H

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
    void updateTable(QMap<QString, uint> syrups);
    ~AllSyrupsWidget();

signals:
    void updateSyrupsTableSignal();

private slots:
    void on_updateButton_clicked();

private:
    QTableWidget* table;
    Ui::AllSyrupsWidget *ui;
};

#endif // ALLSYRUPSWIDGET_H
