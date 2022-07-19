#include "drink.h"

Drink::Drink()
{

}

Drink::Drink(QString name, uint price, uint number) {
    _name = name;
    _price = price;
    _number = number;
}

void Drink::setName(QString name) {
    _name = name;
}

void Drink::setNumber(uint number) {
    _number = number;
}

void Drink::setPrice(uint price) {
    _price = price;
}

QString Drink::getName() {
    return _name;
}

uint Drink::getNumber() {
    return _number;
}

uint Drink::getPrice() {
    return _price;
}
