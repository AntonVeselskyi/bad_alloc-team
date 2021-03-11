#pragma once

#include "entities.h"

void mark_as_covered(Antenna &antenna, Building &building, vector<vector<Building *>> &grid) {
    building.visited = true;

    auto marker = [&](auto x, auto y) {
        if (!(0 <= y && y < grid.size()))
            return;
        if (!(0 <= x && x < grid[y].size()))
            return;

        auto b = grid[y][x];
        if (b != nullptr)
            b->visited = true;
    };

    for (auto r = antenna.range; r > 0; r--) {
        for (auto i = 0; i < r; i++) {
            auto j = r - i;

            marker(antenna.x + i, antenna.y + j);
            marker(antenna.x + i, antenna.y - j);
            marker(antenna.x - i, antenna.y + j);
            marker(antenna.x - i, antenna.y - j);
            marker(antenna.x + j, antenna.y + i);
            marker(antenna.x + j, antenna.y - i);
            marker(antenna.x - j, antenna.y + i);
            marker(antenna.x - j, antenna.y - i);
        }
    }
}