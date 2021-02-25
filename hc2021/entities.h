//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_ENTITIES_H
#define HC2018_ENTITIES_H

#include <vector>
#include <list>
#include <utility>

using StreetID = size_t;
using CarID = size_t;
using IntersectionID = size_t;
using TrafficLightSchedule = std::pair<StreetID, ssize_t>;

struct Car {
    CarID id;
    size_t road_time = 0;
    std::vector<StreetID> path;
};

struct Street {
    StreetID id;
    size_t duration;
    std::vector<CarID> queue;
};

struct Intersection {
    IntersectionID id;
    std::list<StreetID> in;
    std::list<StreetID> out;
    std::vector<TrafficLightSchedule> schedule;
};

#endif //HC2018_ENTITIES_H
