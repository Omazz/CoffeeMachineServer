#include "coffeemachine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoffeeMachine w;
    w.setFixedSize(w.width(), w.height());
    w.show();
    return a.exec();
}
