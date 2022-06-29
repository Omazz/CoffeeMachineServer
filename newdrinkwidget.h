#ifndef NEWDRINKWIDGET_H
#define NEWDRINKWIDGET_H

#include <QDialog>

namespace Ui {
class newDrinkWidget;
}

class newDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    explicit newDrinkWidget(QWidget *parent = nullptr);
    ~newDrinkWidget();

private:
    Ui::newDrinkWidget *ui;
};

#endif // NEWDRINKWIDGET_H
