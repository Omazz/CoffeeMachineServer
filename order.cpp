#include "order.h"

Order::Order() {

}

Order::Order(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  QString syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}

void Order::setOrder(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  QString syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}

QString Order:: getDrink()
{
    return drink;
}

QString Order:: getSyrup()
{
    return syrup;
}

bool Order:: isNeededSugar()
{
    return sugarIsNeeded;
}

bool Order:: isNeededMilk()
{
    return milkIsNeeded;
}

bool Order:: isNeededCinnamon()
{
    return cinnamonIsNeeded;
}
