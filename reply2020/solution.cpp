#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"
#include "clusterize.h"
#include "islands.h"


void print_users(FileOutput &fo, const vector<User> &users)
{
    for (auto us: users)
    {
        if (us.pos == NOT_SET)
            fo.write_line('X');
        else
            fo.write_line(us.pos.second, us.pos.first);
    }
}

int main(int argc, char *argv[])
{
    //GET INPUT
    FileParser parser(argv[1]);

    int width, height;
    parser.get_next_line(width, height);

    Room room{width, height};
    vector<User> devs;
    vector<User> pms;

    vector<Place> row(width);
    for (int i = 0; i < height; i++) {
        room.area.emplace_back();

        string r;
        parser.get_next_line(r);

        for (auto& c : r)
            room.area[i].push_back((Place) c);
    }

    int devs_number;
    parser.get_next_line(devs_number);

    for (int i = 0; i < devs_number; i++){
        string company;
        int bonus, skills_number;

        parser.get_next_line(company, bonus, skills_number);
        User dev{company, bonus, 0,{}  ,Role::DEV};

        for (int j =0; j < skills_number; j++) {
            std::string skill;
            parser.get_next_line(skill);
            dev.skills.push_back(move(skill));
        }

        devs.push_back(move(dev));
    }

    int pms_number;
    parser.get_next_line(pms_number);

    for (int i = 0; i< pms_number; i++){
        string company;
        int bonus;

        parser.get_next_line(company, bonus);

        pms.push_back(User {company, bonus, 0,{}, Role::PM});
    }

    //CLUSTERIZE BY COMPANY
    //map of strings and User* vectors

    //DEVs
    auto devs_map = clusterize(devs);
 
    //PMs
    auto pms_map = clusterize(pms);
    
    //TEST LOG
#ifdef DEBUG
    for (auto &x: devs_map)
    {
        cout << x.first << " has workers: ";
        for (auto &i : x.second)
            cout << i->bonus;
        cout << endl;
    }
#endif
    auto islands = find_islands(room);

    //OUTPUT
    FileOutput output(string(argv[1])+"_res");
    //print out devs and pms
    print_users(output, devs);
    print_users(output, pms);
}
