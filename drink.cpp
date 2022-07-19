#include "drink.h"

Drink::Drink()
{

}

Drink::Drink(QString name, uint price, uint number) {
    this->name = name;
    this->price = price;
    this->number = number;
}

void Drink::setName(QString name) {
    this->name = name;
}

void Drink::setNumber(uint number) {
    this->number = number;
}

void Drink::setPrice(uint price) {
    this->price = price;
}

QString Drink::getName() {
    return name;
}

uint Drink::getNumber() {
    return number;
}

uint Drink::getPrice() {
    return price;
}
