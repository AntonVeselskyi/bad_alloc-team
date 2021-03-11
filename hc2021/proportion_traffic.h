//
// Created by drike on 25.02.2021.
//
#include <map>
#include <numeric>
#include <cmath>
#include <utility>
#include <random>
#include "entities.h"

#pragma once

std::map<StreetID, unsigned> count_street_load(const std::vector<Car> &cars) {
    std::map<StreetID, unsigned> streets_load;
    for (auto &car : cars) {
        for (auto &street_id : car.path) {
            streets_load[street_id]++;
        }
    }

    return streets_load;
}

//ALTER THE 1st PARAMETER
void create_proportional_schedulers(
        std::vector<Intersection> &intersects,
        std::map<StreetID, unsigned> streets_load,
        size_t sim_length,
        std::vector<Street> &streets
) {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    for (auto &intersect : intersects) {
        //traffic lights only on IN streets
        {
            std::vector<std::pair<StreetID, int>> load;

            for (auto &in_street : intersect.in) {
                if (streets_load[in_street])
                    load.emplace_back(in_street, streets_load[in_street]);
            }

            if (load.empty())
                continue;

            std::sort(
                    load.begin(),
                    load.end(),
                    [](auto &a, auto &b) { return a.second > b.second; }
            );

            int max_score = std::min((int) sim_length, 2);
            std::vector<std::pair<StreetID, int>> result;

            for (auto &it: load) {
                result.emplace_back(it.first, max_score);
                if (max_score > 1)
                    max_score--;
            }

            std::shuffle(result.begin(), result.end(), rng);
            for (auto &it: result) {
                intersect.schedule.push_back(it);
            }
        }
    }
}