#ifndef ALLSYRUPSWIDGET_H
#define ALLSYRUPSWIDGET_H

#include <QDialog>

namespace Ui {
class AllSyrupsWidget;
}

class AllSyrupsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AllSyrupsWidget(QWidget *parent = nullptr);
    ~AllSyrupsWidget();

private:
    Ui::AllSyrupsWidget *ui;
};

#endif // ALLSYRUPSWIDGET_H
