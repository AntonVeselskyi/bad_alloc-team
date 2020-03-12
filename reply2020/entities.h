//
// Created by Yurii Karabas on 3/12/20.
//

#ifndef REPLY2020_ENTITIES_H
#define REPLY2020_ENTITIES_H

#include <string>
#include <vector>
#include <cstdint>
#include <utility>

using Pos = std::pair<int, int>;

using namespace std;

enum Place {
    UNAVAILABLE = '#',
    DEV_FREE = '_',
    PM_FREE = 'M',
    DEV_USED = '*',
    PM_USED = '$'
};

enum Role {
    DEV,
    PM
};

struct Room {
    int width;
    int height;
    vector<vector<Place>> area;
};

struct User {
    std::string company;
    uint8_t bonus;
    std::vector<std::string> skills;
    Role role;
    Pos pos;
};

#endif //REPLY2020_ENTITIES_H
