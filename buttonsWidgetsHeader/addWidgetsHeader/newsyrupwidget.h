#ifndef NEWSYRUPWIDGET_H
#define NEWSYRUPWIDGET_H

#include <QDialog>

namespace Ui {
class NewSyrupWidget;
}

class NewSyrupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewSyrupWidget(QWidget *parent = nullptr);
    ~NewSyrupWidget();

signals:
    void newSyrupSignal(QString syrup, QString price);

private slots:
    void on_sendToDatabaseButton_clicked();

private:
    Ui::NewSyrupWidget* _ui;
};

#endif // NEWSYRUPWIDGET_H
