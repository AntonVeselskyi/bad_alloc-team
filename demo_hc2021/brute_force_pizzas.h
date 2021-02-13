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
    auto a_iter = begin(pizzas), b_iter = begin(pizzas);

    for(auto a = begin(pizzas); a != end(pizzas); a++)
        for(auto b = next(a); b != end(pizzas); b++)
        {
            size_t cur_res = score({a, b});
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
    auto a_iter = begin(pizzas), b_iter = begin(pizzas), c_iter = begin(pizzas);

    for(auto a = begin(pizzas); a != end(pizzas); a++)
        for(auto b = next(a); b != end(pizzas); b++)
            for(auto c = next(b); c != end(pizzas); c++)
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
    auto a_iter = begin(pizzas), b_iter = begin(pizzas),
    c_iter = begin(pizzas), d_iter = begin(pizzas);

    for(auto a = begin(pizzas); a != end(pizzas); a++)
        for(auto b = next(a); b != end(pizzas); b++)
            for(auto c = next(b); c != end(pizzas); c++)
                for(auto d = next(c); d != end(pizzas); d++)
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

