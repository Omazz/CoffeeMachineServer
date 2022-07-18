#ifndef CHANGEPRICEDRINKWIDGET_H
#define CHANGEPRICEDRINKWIDGET_H

#include <QDialog>

namespace Ui {
class ChangePriceDrinkWidget;
}

class ChangePriceDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePriceDrinkWidget(QWidget *parent = nullptr);
    ~ChangePriceDrinkWidget();

signals:
    void changePriceDrinkSignal(QString drink, QString price);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePriceDrinkWidget *ui;
};

#endif // CHANGEPRICEDRINKWIDGET_H
