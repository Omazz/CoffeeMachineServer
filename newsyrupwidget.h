#ifndef NEWSYRUPWIDGET_H
#define NEWSYRUPWIDGET_H

#include <QDialog>

namespace Ui {
class newSyrupWidget;
}

class newSyrupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit newSyrupWidget(QWidget *parent = nullptr);
    ~newSyrupWidget();

private:
    Ui::newSyrupWidget *ui;
};

#endif // NEWSYRUPWIDGET_H
