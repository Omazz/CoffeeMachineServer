#include "coffeemachine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoffeeMachine w;
    w.show();
    return a.exec();
}
