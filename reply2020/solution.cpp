#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"

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
        User dev{company, bonus, {}, Role::DEV};

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

        pms.push_back(User {company, bonus, {}, Role::PM});
    }

    auto res = {1,2,3};
    FileOutput output(string(argv[1])+"_res");
    output.write_line(res.size());

    for (auto it: res)
    {
        output.write_line(it);
        for (auto jt: {7, 7, 7}) {
            output.write(jt);
            output.write(" ");
        }
        output.write("\n");
    }



    // //WRITE RESULTS TO FILE
    // int res1 = 200, res2 = 99;
    // float res3 = 2.2;
    // auto res_vec = {"cool", "stuff"};

    // FileOutput output(string(argv[1])+"_res");
    // output.write_line(res1, res2, res3);
    // for(auto el: res_vec)
    //     output.write_line(el);

}
