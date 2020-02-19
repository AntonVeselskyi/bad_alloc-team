#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#include "Ride.h"
#include "parser.h"
#include "Car.h"

struct Settings
{
    int R,C,F,N,B,T;
}global_conf;

int main(int argc, char* argv[])
{
    //Set up
    auto main_queue = parse_data(argv[1], global_conf);

    vector<Car> cars;
    for(int i = 0; i < global_conf.F, ++i)
        cars.emplace_back(Car(main_queue));
    
    //Simulate
    for(unsigned step = 0; step < global_conf.T; ++step)
    {
        for(Car &cur_car : cars)
            car.tick(step);
    }

    //write results to file
    std::ofstream ofs ("res.txt", std::ofstream::out);

    ofs << good_indxs.size() << endl;
    for(Car &cur_car : cars)
    {
        vector<int> done_rides = car.get_done_rides();
        ofs << done_rides.size();
        for(auto i : done_rides)
            ofs << " " << i;
        ofs << endl;
    }
    ofs.close();
    

}
