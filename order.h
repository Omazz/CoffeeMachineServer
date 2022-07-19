#ifndef ORDER_H
#define ORDER_H

#include "drink.h"
#include "syrup.h"

#include <QString>

class Order
{
public:
    Order();
    Order(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded, Syrup syrup);
    void setOrder(Drink drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded, Syrup syrup);
    Drink getDrink();
    Syrup getSyrup();
    bool isNeededSugar();
    bool isNeededMilk();
    bool isNeededCinnamon();
private:
    Drink drink;
    bool sugarIsNeeded;
    bool milkIsNeeded;
    bool cinnamonIsNeeded;
    Syrup syrup;
};

#endif // ORDER_H
