//
// Created by Yurii Karabas on 13/02/2021.
//

#pragma once

#include <vector>
#include <list>
#include <utility>
#include <unordered_map>

struct Building
{
    std::size_t x,y, latency_w, connection_speed_w;
};

struct Antenna
{
    std::size_t range, connection_speed;
    std::size_t id, x, y;

};
using namespace std;