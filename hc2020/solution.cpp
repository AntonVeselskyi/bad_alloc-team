#include <iostream>
#include <list>
#include "getline.h"
#include "output.h"

using namespace std;

struct Book
{
    int number;
    int score;
};

int main(int argc, char *argv[])
{
    //GET INPUT
    FileParser parser(argv[1]);
    int booksCount,
        libCount,
        days;

    parser.get_next_line(booksCount, libCount, days);

    cout << booksCount << libCount << days << endl;

    // for(int i = 0; i <  gc.B; ++i)
    // {
    //     int first, second;
    //     parser.get_next_line(first, second);

    //     cout << first << second << endl;
    // }


    // //PROCESS INPUT


    // //WRITE RESULTS TO FILE
    // int res1 = 200, res2 = 99;
    // float res3 = 2.2;
    // auto res_vec = {"cool", "stuff"};
    
    // FileOutput output(string(argv[1])+"_res");
    // output.write_line(res1, res2, res3);
    // for(auto el: res_vec)
    //     output.write_line(el);

}