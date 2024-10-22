//
// Created by Yurii Karabas on 3/12/20.
//

#ifndef REPLY2020_ENTITIES_H
#define REPLY2020_ENTITIES_H

#include <string>
#include <vector>
#include <cstdint>
#include <utility>
#include <algorithm>


using Pos = std::pair<int, int>;

const Pos NOT_SET = Pos(-1, -1);

using namespace std;



enum Place : char {
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

Place get_place(Room &room, Pos &pos) {
    return room.area[pos.first][pos.second];
}

struct User {
    std::string company;
    int bonus;
    float avg_cluster_score;
    std::list<std::string> skills;
    Role role;
    Pos pos = NOT_SET;

    bool operator<(const User &rhs) const {
        if (role == PM)
            return this->bonus > rhs.bonus;
        else //DEV
            return this->avg_cluster_score > rhs.avg_cluster_score;
    }
};


long long score(const User &a, const User &b) {

    //work potential
    long WP = 0,
    //bonus potential
            BP = 0;
    std::list<string> skills_intersection;
    std::set_intersection(a.skills.begin(), a.skills.end(), b.skills.begin(), b.skills.end(),
                          std::back_inserter(skills_intersection));

    std::list<string> skills_union;
    std::set_union(a.skills.begin(), a.skills.end(), b.skills.begin(), b.skills.end(),
                   std::back_inserter(skills_union));

    WP = skills_intersection.size() + (skills_union.size() - skills_intersection.size());
    BP = a.company == b.company ? a.bonus * b.bonus : 0;

    return WP + BP;
}


#endif //REPLY2020_ENTITIES_H
