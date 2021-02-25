//
// Created by drike on 25.02.2021.
//
#include <map>
#include <numeric>
#include <cmath>
#include "entities.h"

#pragma once

std::map<StreetID, unsigned> count_street_load(const std::vector<Car> &cars)
{
    std::map<StreetID, unsigned> streets_load;
    for(auto &car : cars)
    {
        for(auto &street_id : car.path)
        {
            streets_load[street_id]++;
        }
    }

    return streets_load;
}

//ALTER THE 1st PARAMETER
void create_proportional_schedulers(std::vector<Intersection> &intersects, std::map<StreetID, unsigned> streets_load)
{
    for(auto &intersect : intersects)
    {
        //traffic lights only on IN streets
        {
            constexpr size_t CYCLE_LENGTH = 24;

            //measured in cars
            unsigned total_intersect_load = std::accumulate(begin(intersect.in), end(intersect.in), 0,
                                                            [&streets_load](StreetID a, StreetID b)
                                                            {
                                                                return streets_load[a] + streets_load[b];
                                                            });
            for(auto &in_street : intersect.in)
            {
                size_t green_seconds_for_street = (size_t)floor(streets_load[in_street] * CYCLE_LENGTH / total_intersect_load);
                intersect.schedule.push_back({in_street, green_seconds_for_street});
            }

        }
    }
}