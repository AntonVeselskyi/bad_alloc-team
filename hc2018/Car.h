#ifndef HASHCODEPREPARATION_CAR_H
#define HASHCODEPREPARATION_CAR_H

#include <utility>
#include <queue>

#include "ride.h"

using namespace std;

#include <utility>

using uint = unsigned int;

class Car {
private:
    Ride *ride;
    queue<Ride *> &rides;
    vector<uint> done_rides;

    Pos position;
    uint steps_to_dest;
public:
    Car(queue<Ride *> &rides);

    void tick(uint step);

    vector<uint> get_done_rides();
};


#endif //HASHCODEPREPARATION_CAR_H
