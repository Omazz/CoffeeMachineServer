#ifndef NEWDRINKWIDGET_H
#define NEWDRINKWIDGET_H

#include <QDialog>

namespace Ui {
class NewDrinkWidget;
}

class NewDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewDrinkWidget(QWidget *parent = nullptr);
    ~NewDrinkWidget();

private slots:
    void on_sendToDatabaseButton_clicked();

signals:
    void newDrinkSignal(QString drink, QString price, QString number);

private:
    Ui::NewDrinkWidget* _ui;
};

#endif // NEWDRINKWIDGET_H
