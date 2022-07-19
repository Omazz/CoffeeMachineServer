#ifndef ALLDRINKSWIDGET_H
#define ALLDRINKSWIDGET_H

#include <QDialog>

namespace Ui {
class AllDrinksWidget;
}

class AllDrinksWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AllDrinksWidget(QWidget *parent = nullptr);
    ~AllDrinksWidget();

private:
    Ui::AllDrinksWidget *ui;
};

#endif // ALLDRINKSWIDGET_H
