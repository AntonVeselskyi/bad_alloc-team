//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_DECIDER_H
#define HC2018_DECIDER_H

#include <tuple>

#include "entities.h"
#include "brute_force_pizzas.h"
#include <cmath>


optional<Delivery> decide(Pizzas &pizzas, int& two_teams, int& three_teams, int& four_teams) {
    vector<vector<pizzas_iter>> options;

    if (two_teams > 0) {
        auto for_two = best_pizzas_for_2(pizzas);
        if (!for_two.empty())
            options.push_back(move(for_two));
    }
    if (three_teams > 0) {
        auto for_three = best_pizzas_for_3(pizzas);
        if (!for_three.empty())
            options.push_back(move(for_three));
    }
    if (four_teams > 0) {
        auto for_four = best_pizzas_for_4(pizzas);
        if (!for_four.empty())
            options.push_back(move(for_four));
    }

    auto best = std::max_element(
            options.begin(),
            options.end(),
            [](auto &a, auto &b) { return score(a) < score(b); }
    );

    if (best == options.end())
        return nullopt;

    switch (best->size()) {
        case 2:
            two_teams--;
            break;
        case 3:
            three_teams--;
            break;
        case 4:
            four_teams--;
            break;
    }

    Delivery result{
            .team = best->size()
    };

    for (const auto &it : *best) {
        result.pizzas.push_back(it->second.back());
        it->second.pop_back();

        if (it->second.empty()) {
            pizzas.erase(it);
        }
    }

    return optional(move(result));
}


#endif //HC2018_DECIDER_H
