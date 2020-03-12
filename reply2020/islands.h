#pragma once

#include <set>
#include <iostream>
#include "entities.h"
#include "emplacer.h"

using Island = vector<Pos>;

Island find_island(Room &room, Pos &start, set<Pos> &visited) {
    Island island;

    queue <Pos> positions;
    positions.push(start);

    visited.insert(start);

    while (!positions.empty()) {
        auto pos = positions.front();

        island.push_back(pos);
        positions.pop();

        for (auto &next : adjustment_free_places(room, pos)) {
            if (visited.find(next) == visited.end()){
                positions.push(next);
                visited.insert(next);
            }
        }
    }

    return island;
}

vector<Island> find_islands(Room &room) {
    vector<Island> islands;
    set<Pos> visited;

    Pos start(0, 0);

    while (true) {
        start = free_place(room, visited, start);

        if (start == NOT_SET)
            break;

        Island island = find_island(room, start, visited);
        islands.push_back(island);
    }

    return islands;
}