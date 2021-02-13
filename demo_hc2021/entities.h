//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_ENTITIES_H
#define HC2018_ENTITIES_H

#include <set>
#include <list>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace std;

struct pizza_hasher
{
    size_t operator()(std::set<std::string> &s) const
    {
        std::hash<std::string> string_hasher;
        size_t res = 23;

        for(const string &str : s)
            res ^= string_hasher(str);

        return res;
    }
};

using Pizza = set<string>;
using PizzaIndex = int;
using PizzaIndexes = vector<PizzaIndex>;

using pizza_map = std::unordered_map<std::set<std::string>, std::vector<int>, pizza_hasher>;
using pizza_map_iter = pizza_map::iterator;

struct Delivery {
    size_t team;
    PizzaIndexes pizzas;
};

#endif //HC2018_ENTITIES_H
