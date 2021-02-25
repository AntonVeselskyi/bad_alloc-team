//
// Created by drike on 25.02.2021.
//
#include <map>
#include <numeric>
#include <cmath>
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
            size_t CYCLE_LENGTH = gcd(sim_length, intersect.in.size());

            unsigned total_intersect_load = 0;
            for (auto &it : intersect.in)
                total_intersect_load += streets_load[it] * streets[it].duration;

            if (!total_intersect_load)
                total_intersect_load = 1;
            for (auto &in_street : intersect.in) {
                size_t green_seconds_for_street = (size_t) floor(
                        (streets_load[in_street] * streets[in_street].duration) * CYCLE_LENGTH / total_intersect_load
                );
                if (green_seconds_for_street)
                    intersect.schedule.push_back({in_street, green_seconds_for_street});
            }

        }
    }
}