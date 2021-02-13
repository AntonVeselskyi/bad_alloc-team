//
// Created by AV on 13.02.2021.
//
#include <unordered_map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <functional>
#include <algorithm>
#include "entities.h"
#include "decider.h"

vector<pizzas_iter> best_pizzas_for_2(Pizzas &pizzas)
{
    if(pizzas.empty())
        return {};

    size_t best_score = 0;
    pizzas_iter a_iter = begin(pizzas), b_iter = begin(pizzas);

    for(auto &a : pizzas)
        for(auto &b : pizzas)
        {
            auto a_set = a.first, b_set = b.first;
            set<std::string> intersection;
            std::set_intersection(begin(a_set), end(a_set), begin(b_set), end(b_set), intersection);

            size_t cur_res = intersection.size() * intersection.size();
            if(best_score < cur_res)
            {
                best_score = cur_res;
                a_iter = a;
                b_iter = b;

            }
        }

            return {a_iter, b_iter};
}

vector<pizzas_iter> best_pizzas_for_3(Pizzas &pizzas)
{
    if(pizzas.empty())
        return {};

    size_t best_score = 0;
    pizzas_iter a_iter = begin(pizzas), b_iter = begin(pizzas), c_iter = begin(pizzas);

    for(auto &a : pizzas)
        for(auto &b : pizzas)
        for(auto &c : pizzas)
        {
            size_t cur_res = score({a, b, c});
            if(best_score < cur_res)
            {
                best_score = cur_res;
                a_iter = a;
                b_iter = b;
                c_iter = c;

            }
        }

    return {a_iter, b_iter, c_iter};
}

vector<pizzas_iter> best_pizzas_for_4(Pizzas &pizzas)
{
    if(pizzas.empty())
        return {};

    size_t best_score = 0;
    pizzas_iter a_iter = begin(pizzas), b_iter = begin(pizzas),
    c_iter = begin(pizzas), d_iter = begin(pizzas);

    for(auto &a : pizzas)
        for(auto &b : pizzas)
            for(auto &c : pizzas)
                for(auto &d : pizzas)
            {
                size_t cur_res = score({a, b, c, d});
                if(best_score < cur_res)
                {
                    best_score = cur_res;
                    a_iter = a;
                    b_iter = b;
                    c_iter = c;
                    d_iter = d;

                }
            }

    return {a_iter, b_iter, c_iter, d_iter};
}

