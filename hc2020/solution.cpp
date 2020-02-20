#include <iostream>
#include "getline.h"
#include "output.h"

using namespace std;

struct Settings
{
    unsigned A, B;
    string C;
}gc; //global conf

int main(int argc, char *argv[])
{
    //GET INPUT
    FileParser parser(argv[1]);
    parser.get_next_line(gc.A, gc.B, gc.C);

    cout << gc.A << gc.B << gc.C << endl;

    for(int i = 0; i <  gc.B; ++i)
    {
        int first, second;
        parser.get_next_line(first, second);

        cout << first << second << endl;
    }


    //PROCESS INPUT


    //WRITE RESULTS TO FILE
    int res1 = 200, res2 = 99;
    auto res_vec = {"cool", "stuff"};
    
    FileOutput output(string(argv[1])+"_res");
    output.write_line(res1, res2);
    for(auto el: res_vec)
        output.write_line(el);

}