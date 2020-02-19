#pragma once

#include <utility>
using namespace std;
using Pos = pair<int, int>;

struct Ride
{
    int index;
    Pos start_pos;
    Pos end_pos;
    int earliest_start;
    int end;
};
