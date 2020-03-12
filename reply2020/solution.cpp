#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <utility>
#include "getline.h"
#include "output.h"


int main(int argc, char *argv[])
{
    //GET INPUT
    FileParser parser(argv[1]);
    int a, b, c;

    parser.get_next_line(a, b, c);

    for (int i = 0; i < a; ++i)
    {
        int award;
        parser.get_next_line(award);
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
