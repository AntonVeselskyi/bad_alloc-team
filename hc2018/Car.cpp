#include "Car.h"

Car::Car(queue<Ride *> rides) : rides(rides), ride(nullptr) {}

void Car::tick(uint step) {

}

bool Car::reach_end() {
    return ride == nullptr;
}

vector<uint> Car::get_done_rides() {
    return done_rides;
}
