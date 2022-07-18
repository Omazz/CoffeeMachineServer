#ifndef DELETESOMEDRINKWIDGET_H
#define DELETESOMEDRINKWIDGET_H

#include <QDialog>

namespace Ui {
class DeleteSomeDrinkWidget;
}

class DeleteSomeDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteSomeDrinkWidget(QWidget *parent = nullptr);
    ~DeleteSomeDrinkWidget();

signals:
    void deleteSomeDrinkSignal(QString drink);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DeleteSomeDrinkWidget *ui;
};

#endif // DELETESOMEDRINKWIDGET_H
