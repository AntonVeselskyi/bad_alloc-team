#include "Car.h"
#include <cmath>

inline uint get_distance(Pos start, Pos end) {
    return abs(end.first - start.first) + abs(end.second - end.first);
}

Car::Car(queue<Ride *>& rides) : rides(rides),
                                ride(nullptr),
                                steps_to_dest(0),
                                position(0, 0) {}

void Car::tick(uint step) {
    if (ride == nullptr) {
        if (!rides.empty()){
            return;
        }

        ride = rides.front();
        rides.pop();

        uint to_start = max(
                get_distance(position, ride->start_pos),
                ride->earliest_start - step
        );
        uint from_start_to_end = get_distance(ride->start_pos, ride->end_pos);

        steps_to_dest = to_start + from_start_to_end;
    }

    steps_to_dest--;

    if (!steps_to_dest) {
        done_rides.push_back(ride->index);
        position = ride->end_pos;

        delete ride;
        ride = nullptr;
    }
}

vector<uint> Car::get_done_rides() {
    return done_rides;
}
