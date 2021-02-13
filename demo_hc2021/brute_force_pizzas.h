//
// Created by AV on 13.02.2021.
//
#include <unordered_map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <functional>
#include <cmath>
#include <algorithm>
#include "entities.h"

size_t score(const vector<pizzas_iter>& iters) {
    Pizza res;

    for(const auto & iter:iters) {
        res.insert(iter->first.begin(), iter->first.end());
    }

    return pow(res.size(), 2);
}

vector<pizzas_iter> best_pizzas_for_2(Pizzas &pizzas)
{
    if(pizzas.empty())
        return {};

    size_t best_score = 0;
    pizzas_iter a_iter = begin(pizzas), b_iter = begin(pizzas);

    for(pizzas_iter a = begin(pizzas); a != end(pizzas); a++)
        for(pizzas_iter b = begin(pizzas); b != end(pizzas); b++)
        {
            auto a_set = a->first, b_set = b->first;
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

    for(pizzas_iter a = begin(pizzas); a != end(pizzas); a++)
        for(pizzas_iter b = begin(pizzas); b != end(pizzas); b++)
            for(pizzas_iter c = begin(pizzas); c != end(pizzas); c++)
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

    for(pizzas_iter a = begin(pizzas); a != end(pizzas); a++)
        for(pizzas_iter b = begin(pizzas); b != end(pizzas); b++)
            for(pizzas_iter c = begin(pizzas); c != end(pizzas); c++)
                for(pizzas_iter d = begin(pizzas); d != end(pizzas); d++)
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

