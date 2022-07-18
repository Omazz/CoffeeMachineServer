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

private:
    Ui::DeleteSomeSyrupWidget *ui;
};

#endif // DELETESOMESYRUPWIDGET_H
