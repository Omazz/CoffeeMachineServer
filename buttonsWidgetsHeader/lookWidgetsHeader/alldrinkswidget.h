#ifndef ALLDRINKSWIDGET_H
#define ALLDRINKSWIDGET_H

#include "drink.h"
#include <QTableWidget>
#include <QDialog>

namespace Ui {
class AllDrinksWidget;
}

class AllDrinksWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AllDrinksWidget(QWidget *parent = nullptr);
    void updateTable(QVector<Drink> drinks);
    ~AllDrinksWidget();

signals:
    void updateDrinksTableSignal();

private slots:
    void on_updateButton_clicked();

private:
    QTableWidget* table;
    Ui::AllDrinksWidget *ui;
};

#endif // ALLDRINKSWIDGET_H
