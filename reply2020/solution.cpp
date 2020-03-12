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
#include "fit.h"


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
    
    //main logic
    auto islands = find_islands(room);

    vector<string> all_companies;

    for(auto &el : devs_map)
        all_companies.push_back(el.first);

    for(auto &comp : all_companies)
    {
        sort_list_by_coolness(devs_map[comp]);
        sort_list_by_greed(pms_map[comp]);
    }

    while(1)
    {
        int cluster_id = 0;
        for(auto &island : islands)
        {
            if(all_companies.empty())
                break;
            if(cluster_id == all_companies.size()-1)
                cluster_id = 0;
            if  (devs_map[(all_companies[cluster_id])].size()+pms_map[(all_companies[cluster_id])].size() < island.size())
            {
                all_companies.erase(all_companies.begin()+cluster_id);
                continue;
            }
            fit_on_island(room, island, devs_map[(all_companies[cluster_id])], pms_map[(all_companies[cluster_id])]);
            cluster_id++;

        }
    }


    //OUTPUT
    FileOutput output(string(argv[1])+"_res");
    //print out devs and pms
    print_users(output, devs);
    print_users(output, pms);
}
