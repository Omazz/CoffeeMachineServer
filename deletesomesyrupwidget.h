#ifndef DELETESOMESYRUPWIDGET_H
#define DELETESOMESYRUPWIDGET_H

#include <QDialog>

namespace Ui {
class DeleteSomeSyrupWidget;
}

class DeleteSomeSyrupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteSomeSyrupWidget(QWidget *parent = nullptr);
    ~DeleteSomeSyrupWidget();

signals:
    void deleteSomeSyrupSignal(QString syrup);

private slots:
    void on_pushButton_clicked();
private:
    Ui::DeleteSomeSyrupWidget *ui;
};

#endif // DELETESOMESYRUPWIDGET_H
