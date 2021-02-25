//
// Created by Yurii Karabas on 13/02/2021.
//

#ifndef HC2018_ENTITIES_H
#define HC2018_ENTITIES_H

#include <vector>
#include <list>
#include <utility>
#include <unordered_map>

using namespace std;

using StreetID = size_t;
using CarID = size_t;
using IntersectionID = size_t;
using TrafficLightSchedule = std::pair<StreetID, ssize_t>;
using TrafficLightSchedules = std::vector<TrafficLightSchedule>;

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
    TrafficLightSchedules schedule;
};

class StreetIndex {
private:
    std::unordered_map<StreetID, std::string> id_to_name;
    std::unordered_map<std::string, StreetID> name_to_id;
    StreetID counter = 0;
public:
    StreetID add(std::string &name) {
        auto it = name_to_id.find(name);
        if (it == name_to_id.end()) {
            name_to_id[name] = counter;
            id_to_name[counter] = name;
            return counter++;
        }

        return it->second;
    }

    std::string &operator[](StreetID id) {
        return id_to_name[id];
    }

    StreetID operator[](std::string &name) {
        return name_to_id[name];
    }
};

#endif //HC2018_ENTITIES_H
