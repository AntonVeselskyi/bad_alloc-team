#pragma once

#include "entities.h"
#include "emplacer.h"

using Island = vector<Pos>;

Island find_island(Room &room, Pos &start, vector<Pos> &visited) {
    Island island;

    queue<Pos> positions;
    positions.push(start);

    while (!positions.empty()) {
        auto pos = positions.front();
        positions.pop();

        visited.push_back(pos);

        for (auto &next : adjustment_free_places(room, pos)) {
            if (!contains(visited, next))
                positions.push(next);
        }
    }

    return island;
}

vector<Island> find_islands(Room &room) {
    vector<Island> islands;
    vector<Pos> visited;

    while (true) {
        auto pos = free_place(room, visited);

        if (pos == NOT_SET)
            break;

        Island island = find_island(room, pos, visited);
    }
}