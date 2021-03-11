#include <iostream>
#include <utility>
#include <algorithm>
#include "getline.h"
#include "output.h"
#include "entities.h"
#include "marker.h"
#include "mover.h"

int main(int argc, char *argv[])
{
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");




    unsigned map_width, map_height,
        buildings_num, antennas_num, reward;
    parser.get_next_line(map_width, map_height);
    parser.get_next_line(buildings_num, antennas_num, reward);

    vector<vector<Building*>> map(map_height+1);
    for(auto &row : map)
        row = vector<Building*>(map_width+1);

    list<Building> b_storage;
    {
        size_t x, y, latency_w, connection_speed_w;
        for (size_t n = buildings_num; n--;)
        {
            parser.get_next_line(x, y, latency_w, connection_speed_w);
            b_storage.emplace_back(Building{x, y, latency_w, connection_speed_w});
            map[y][x] = &b_storage.back();
        }
    }

    vector<Antenna> a_storage;
    a_storage.reserve(antennas_num);
    {
        size_t a, b;
        for (size_t id = 0; id <  antennas_num; id++)
        {

            parser.get_next_line(a,b);
            a_storage.emplace_back(Antenna{a,b, id});
        }
    }


    //straight forward solution
    b_storage.sort(
              [](const Building &a, const Building &b)
              {
                  return a.latency_w !=  b.latency_w ? a.latency_w > b.latency_w : a.connection_speed_w > b.connection_speed_w;
              });

    std::sort(begin(a_storage), end(a_storage),
              [](const Antenna &a, const Antenna &b)
              {
                  return a.range !=  b.range ? a.range > b.range : a.connection_speed > b.connection_speed;
              });

    for(auto [i, b_iter] = std::tuple{0, begin(b_storage)};
        i < antennas_num && b_iter != end(b_storage);\
        ++b_iter)
    {
        if(b_iter->visited)
            continue;

        a_storage[i].x = b_iter->x;
        a_storage[i].y = b_iter->y;
        move_antenna_from_border(a_storage[i], map_width, map_height);

        mark_as_covered(a_storage[i], *b_iter, map);

        ++i;
    }
    output.print_result(a_storage);

}