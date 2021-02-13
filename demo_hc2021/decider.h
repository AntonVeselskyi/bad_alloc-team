//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_DECIDER_H
#define HC2018_DECIDER_H

#include <tuple>

#include "entities.h"
#include "brute_force_pizzas.h"


int score(vector<pizzas_iter>& iters) {

}

optional<Delivery> decide(Pizzas &pizzas, int& two_teams, int& three_teams, int& four_teams) {
    vector<vector<pizzas_iter>> options;

    if (two_teams > 0) {
        auto for_two = best_pizzas_for_2(pizzas);
        if (for_two.size() > 0)
            options.push_back(move(for_two));
    }
    if (three_teams > 0) {
        auto for_three = best_pizzas_for_2(pizzas);
        if (for_three.size() > 0)
            options.push_back(move(for_three));
    }
    if (four_teams > 0) {
        auto for_four = best_pizzas_for_2(pizzas);
        if (for_four.size() > 0)
            options.push_back(move(for_four));
    }
}


#endif //HC2018_DECIDER_H
