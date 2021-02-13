//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_ENTITIES_H
#define HC2018_ENTITIES_H

#include <set>
#include <list>
#include <string>

using namespace std;

using Pizza = set<reference_wrapper<string>>;
using PizzaIndex = size_t;

struct Delivery {
    size_t team;
    list<PizzaIndex> pizzas;
};

#endif //HC2018_ENTITIES_H
