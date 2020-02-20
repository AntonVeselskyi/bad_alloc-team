#include <iostream>
#include "getline.h"

using namespace std;

struct Settings
{
    unsigned A, B, C;
}gc; //global conf

int main(int argc, char *argv[])
{
    FileParser parser(argv[1]);
    parser.get_next_line(gc.A, gc.B, gc.C);

    cout << gc.A << gc.B << gc.C << endl;

    for(int i = 0; i <  gc.B; ++i)
    {
        int first, second;
        parser.get_next_line(first, second);

        cout << first << second << endl;

    }
}