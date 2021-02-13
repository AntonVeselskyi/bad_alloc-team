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

struct pizza_hasher {
    size_t operator()(const std::set<std::string> &s) const {
        //res = std::hash<std::string>(*s.begin());
        //calculate hash here.
        return 0;
    }
};

using Pizza = set<string>;
using PizzaIndex = int;
using PizzaIndexes = vector<PizzaIndex>;
using Pizzas = std::unordered_map<std::set<std::string>, std::vector<int>, pizza_hasher>;
using pizzas_iter = Pizzas::iterator;

struct Delivery {
    size_t team;
    PizzaIndexes pizzas;
};

#endif //HC2018_ENTITIES_H
