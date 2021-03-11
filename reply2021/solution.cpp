#include <iostream>
#include <utility>
#include <algorithm>
#include "getline.h"
#include "output.h"
#include "entities.h"


int main(int argc, char *argv[])
{
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");


    unsigned map_width, map_height,
        buildings_num, antennas_num, reward;
    parser.get_next_line(map_width, map_height);
    parser.get_next_line(buildings_num, antennas_num, reward);

    vector<Building> b_storage;
    b_storage.reserve(buildings_num);
    {
        size_t x, y, latency_w, connection_speed_w;
        for (size_t n = buildings_num; n--;)
        {
            parser.get_next_line(x, y, latency_w, connection_speed_w);
            b_storage.emplace_back(Building{x, y, latency_w, connection_speed_w});
        }
    }

    vector<Antenna> a_storage;
    a_storage.reserve(antennas_num);
    {
        size_t a, b;
        for (size_t n = antennas_num; n--;)
        {
            parser.get_next_line(a,b);
            a_storage.emplace_back(Antenna{a,b});
        }
    }


    //straight forward solution
    std::sort(begin(b_storage), end(b_storage),
              [](const Building &a, const Building &b)
              {
                    return a.latency_w > b.latency_w;
              });
    for(int i = 0; i < antennas_num && i < buildings_num; ++i)
    {
        a_storage[i].x = b_storage[i].x;
        a_storage[i].y = b_storage[i].y;
    }
    output.print_result(a_storage);

}