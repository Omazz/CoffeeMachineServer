#include "syrup.h"

Syrup::Syrup()
{

}

Syrup::Syrup(QString name, uint price) {
    _name = name;
    _price = price;
}

void Syrup::setName(QString name) {
    _name = name;
}

void Syrup::setPrice(uint price) {
    _price = price;
}

QString Syrup::getName() {
    return _name;
}

uint Syrup::getPrice() {
    return _price;
}
