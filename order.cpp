#include "order.h"

Order::Order() {

}

Order::Order(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  Syrup syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}

void Order::setOrder(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  Syrup syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}

Drink Order:: getDrink()
{
    return drink;
}

Syrup Order:: getSyrup()
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
