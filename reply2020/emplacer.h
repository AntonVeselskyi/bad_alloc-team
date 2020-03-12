#pragma one

#include <queue>
#include <map>
#include "entities.h"

using Users = list<User *>;
using Cluster = map<string, Users>;

vector<Pos> STEPS = {
        {0,  -1},
        {-1, 0},
        {0,  1},
        {1,  0}
};

bool is_place_free(Place &place) {
    return place == Place::DEV_FREE || place == Place::PM_FREE;
}

Pos free_place(Room &room, set<Pos> &visited, Pos& start) {
    for (int i = start.first; i < room.height; i++) {
        for (int j = 0; j < room.width; j++) {
            if (is_place_free(room.area[i][j])) {
                Pos pos(i, j);

                if (visited.find(pos) == visited.end())
                    return pos;
            }
        }
    }

    return NOT_SET;
}

Pos add_pos(Pos &a, Pos &b) {
    return Pos(a.first + b.first, a.second + b.second);
}

bool is_valid_pos(Room &room, Pos &pos) {
    return (pos.first >= 0 && pos.first < room.height) &&
           (pos.second >= 0 && pos.second < room.width);
}

vector<Pos> adjustment_free_places(Room &room, Pos &pos) {
    vector<Pos> adjustment;

    for (auto &step : STEPS) {
        auto next = add_pos(pos, step);

        if (is_valid_pos(room, next) && is_place_free(room.area[next.first][next.second]))
            adjustment.push_back(next);
    }

    return adjustment;
}