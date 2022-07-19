#include "order.h"

Order::Order() {

}

Order::Order(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  Syrup syrup)
{
    _drink = drink;
    _sugarIsNeeded = sugarIsNeeded;
    _milkIsNeeded = milkIsNeeded;
    _cinnamonIsNeeded = cinnamonIsNeeded;
    _syrup = syrup;
}

void Order::setOrder(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  Syrup syrup)
{
    _drink = drink;
    _sugarIsNeeded = sugarIsNeeded;
    _milkIsNeeded = milkIsNeeded;
    _cinnamonIsNeeded = cinnamonIsNeeded;
    _syrup = syrup;
}

Drink Order:: getDrink()
{
    return _drink;
}

Syrup Order:: getSyrup()
{
    return _syrup;
}

bool Order:: isNeededSugar()
{
    return _sugarIsNeeded;
}

bool Order:: isNeededMilk()
{
    return _milkIsNeeded;
}

bool Order:: isNeededCinnamon()
{
    return _cinnamonIsNeeded;
}
