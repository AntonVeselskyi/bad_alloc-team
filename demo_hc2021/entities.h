//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_ENTITIES_H
#define HC2018_ENTITIES_H

#include <set>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

using Pizza = set<string>;
using PizzaIndex = int;
using PizzaIndexes = vector<PizzaIndex>;
using Pizzas = std::unordered_map<Pizza, PizzaIndex>;

struct Delivery {
    size_t team;
    PizzaIndexes pizzas;
};

#endif //HC2018_ENTITIES_H
