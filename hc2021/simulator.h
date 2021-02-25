//
// Created by Yurii Karabas on 25.02.2021.
//

#ifndef HC2018_SIMULATOR_H
#define HC2018_SIMULATOR_H

#include "entities.h"

void simulator_tick(
        std::vector<Intersection> &intersections,
        std::vector<Car> &cars,
        std::vector<Street> &streets
) {
    for (auto &intersection : intersections) {
        auto &street = streets[intersection.activeStreet()];

        if (!street.queue.empty()) {
            auto carID = street.queue.front();
            street.queue.erase(street.queue.begin());

            auto &car = cars[carID];
            car.path.erase(car.path.begin());

            if (!car.path.empty()) {
                car.road_time = car.path.front();
                car.is_moving = true;
            }
        }

        intersection.tick();
    }

    for (auto &car: cars) {
        if (!car.is_moving) {
            continue;
        }

        car.road_time--;

        if (car.road_time <= 0) {
            car.is_moving = false;
            streets[car.path.front()].queue.push_back(car.id);
        }
    }
}

#endif //HC2018_SIMULATOR_H
