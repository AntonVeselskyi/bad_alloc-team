//
// Created by AV on 13.02.2021.
//
#include <unordered_map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <functional>

struct pizza_hasher {
    size_t operator()(const std::set<std::string>& s) const
    {
        //res = std::hash<std::string>(*s.begin());
        //calculate hash here.
        return 0;
    }
};


using pizza_map = std::unordered_map<std::set<std::string>, std::vector<int>, pizza_hasher>;
using pizza_map_iter = pizza_map::iterator;

auto best_pizzas_for_2(pizza_map &map)
{
    return std::make_tuple(map.begin(), map.begin());
}
