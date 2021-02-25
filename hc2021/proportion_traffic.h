//
// Created by drike on 25.02.2021.
//
#include <map>
#include <numeric>
#include <cmath>
#include <utility>
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
    for (auto &intersect : intersects) {
        //traffic lights only on IN streets
        {
            std::vector<std::pair<StreetID, int>> load;
            for (auto &in_street : intersect.in) {
                if (streets_load[in_street])
                    load.emplace_back(in_street, streets_load[in_street]);
            }

            for (auto &it: load) {
                intersect.schedule.push_back({it.first, 1});
            }
        }
    }
}