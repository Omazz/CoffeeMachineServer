#ifndef DRINK_H
#define DRINK_H

#include <QtCore>

class Drink
{
public:
    Drink();
    Drink(QString, uint price, uint number);
    void setName(QString name);
    void setPrice(uint price);
    void setNumber(uint number);
    QString getName();
    uint getPrice();
    uint getNumber();

private:
    QString _name;
    uint _price;
    uint _number;
};

#endif // DRINK_H
