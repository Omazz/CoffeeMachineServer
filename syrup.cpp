#include "syrup.h"

Syrup::Syrup()
{

}

Syrup::Syrup(QString name, uint price) {
    this->name = name;
    this->price = price;
}

void Syrup::setName(QString name) {
    this->name = name;
}

void Syrup::setPrice(uint price) {
    this->price = price;
}

QString Syrup::getName() {
    return name;
}

uint Syrup::getPrice() {
    return price;
}
