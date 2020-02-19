#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#include "ride.h"
#include "parse.h"
#include "Car.h"
#include "settings.h"

int main(int argc, char* argv[])
{
    //Set up
    Settings global_conf; 
    auto main_queue = parse_data(argv[1], global_conf);

    vector<Car> cars;
    for(int i = 0; i < global_conf.F; ++i)
        cars.emplace_back(Car(main_queue));
    
    //Simulate
    for(unsigned step = 0; step < global_conf.T; ++step)
    {
        for(Car &cur_car : cars)
            cur_car.tick(step);
    }

    //write results to file
    std::ofstream ofs ("res.txt", std::ofstream::out);

    for(Car &cur_car : cars)
    {
        vector<uint> done_rides = cur_car.get_done_rides();
        ofs << done_rides.size();
        for(auto i : done_rides)
            ofs << " " << i;
        ofs << endl;
    }
    ofs.close();
    

}
