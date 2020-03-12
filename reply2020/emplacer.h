#pragma one

#include <queue>
#include <map>
#include "entities.h"

using Users = vector<User *>;
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

bool contains(vector<Pos> &vec, Pos &value) {
    return find(vec.begin(), vec.end(), value) != vec.end();
}

Pos free_place(Room &room, vector<Pos> &visited) {
    for (int i = 0; i < room.height; i++) {
        for (int j = 0; j < room.width; j++) {
            if (is_place_free(room.area[i][j])) {
                Pos pos(i, j);

                if (!contains(visited, pos))
                    return pos;
            }
        }
    }

    return NOT_SET;
}

Pos free_place(Room &room) {
    vector<Pos> visited;
    return free_place(room, visited);
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

User *freeUser(Users &users) {
    for (auto &user: users) {
        if (user->pos == NOT_SET)
            return user;
    }

    return nullptr;
}


void set_place(Room &room, Pos &pos, Place &place) {
    room.area[pos.first][pos.second] = place;
}

bool emplace_cluster(Room &room, Users &devs, Users &pms) {
    queue <Pos> positions;

    Pos free = free_place(room);

    if (free == NOT_SET)
        return false;

    positions.push(free);

    while (!positions.empty()) {
        auto pos = positions.front();
        positions.pop();

        auto place = get_place(room, pos);
        User *user;
        Place used_by = UNAVAILABLE;

        if (place == Place::PM_FREE) {
            user = freeUser(pms);
            used_by = Place::PM_USED;
        } else {
            user = freeUser(devs);
            used_by = Place::DEV_USED;
        }

        if (user == nullptr)
            break;

        set_place(room, pos, used_by);

        user->pos = pos;

        for (auto &next : adjustment_free_places(room, pos)) {
            positions.push(next);
        }
    }

    return true;
}

void emplace(Room &room, Cluster &devs, Cluster &pms) {
    for (auto &cluster : devs) {
        auto pms_users = pms.find(cluster.first) != pms.end() ? pms[cluster.first] : Users();

        auto has_more_free = emplace_cluster(room, cluster.second, pms_users);

        if (!has_more_free)
            return;
    }
}