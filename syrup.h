#ifndef SYRUP_H
#define SYRUP_H

#include <QtCore>

class Syrup
{
public:
    Syrup();
    Syrup(QString name, uint price);
    void setName(QString name);
    void setPrice(uint price);
    QString getName();
    uint getPrice();

private:
    QString name;
    uint price;
};

#endif // SYRUP_H
