#include <iostream>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"
#include "proportion_traffic.h"


int main(int argc, char *argv[]) {
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");

    StreetIndex streetIndex;
    int simulationDuration, numberOfIntersections,
            numberOfStreets, numberOfCars, finishBonus;

    parser.get_next_line(simulationDuration, numberOfIntersections,
                         numberOfStreets, numberOfCars, finishBonus);

    std::vector<Street> streets;
    streets.reserve(numberOfStreets);
    std::vector<Car> cars;
    cars.reserve(numberOfCars);
    std::vector<Intersection> intersections(numberOfIntersections);

    for (int i = 0; i < numberOfStreets; i++) {
        int from;
        int to;
        std::string name;
        size_t time;
        parser.get_next_line(from, to, name, time);
        Street street{
                .id = streetIndex.add(name),
                .duration = time,
        };
        intersections[from].out.push_back(street.id);
        intersections[from].id = from;
        intersections[to].in.push_back(street.id);
        intersections[to].id = to;
    }
    for (int i = 0; i < numberOfCars; i++) {
        int numberOfStreetsForCar;
        Car car;
        car.id = i;
        parser.get_next_line(numberOfStreetsForCar);
        for (int j = 0; j < numberOfStreetsForCar; j++) {
            std::string streetName;
            parser.get_next_line(streetName);
            car.path.push_back(streetIndex.add(streetName));
        }
        cars.push_back(car);
    }

    auto streetLoad = count_street_load(cars);
    create_proportional_schedulers(intersections, streetLoad);

    output.print_result(intersections, streetIndex);
#ifdef DEBUG
    for (int i = 0; i < numberOfStreets; i++) {
        cout << " " << streetIndex[i];
        cout << '\n';
    }

    for (auto &car : cars) {
        cout << "car id:" << car.id << " road time: " << car.road_time;
        for (auto &streetId : car.path) {
            cout << " " << streetIndex[streetId];
        }
        cout << '\n';
    }

    cout << "intersections --------------------------\n";
    for (auto &intersection : intersections ) {
        cout << "id:  " << intersection.id << "\n";
        cout << "in:  \n";

        for(auto &in : intersection.in) {
            cout << ' ' << streetIndex[in] << endl;
        }
        cout << "out:  \n";

        for(auto &out : intersection.out) {
            cout << ' ' << streetIndex[out] << endl;
        }
    }
#endif
}