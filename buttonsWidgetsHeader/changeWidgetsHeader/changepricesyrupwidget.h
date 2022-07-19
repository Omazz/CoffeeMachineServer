#ifndef CHANGEPRICESYRUPWIDGET_H
#define CHANGEPRICESYRUPWIDGET_H

#include <QDialog>

namespace Ui {
class ChangePriceSyrupWidget;
}

class ChangePriceSyrupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePriceSyrupWidget(QWidget *parent = nullptr);
    ~ChangePriceSyrupWidget();

signals:
    void changePriceSyrupSignal(QString syrup, QString price);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePriceSyrupWidget* _ui;
};

#endif // CHANGEPRICESYRUPWIDGET_H
