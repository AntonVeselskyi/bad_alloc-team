#include <iostream>
#include <fstream>
#include <queue>
#include <string>

#include "settings.h"
using namespace std;

queue<Ride*> parse_data(const char *fileName, Settings &params)
{
    queue<Ride*> result;

    fstream file;
    file.open(fileName);

    if (file.is_open())
    {
        file >> params.R >> params.C >> params.F >> params.N >> params.B >> params.T;

        int index = 0;
        while (index < params.N)
        {
            Ride *rd = new Ride();
            rd->index = index;

            int a = 0, b = 0;
            file >> a >> b;
            rd->start_pos = make_pair(a, b);

            int x = 0, y = 0;
            file >> x >> y;
            rd->end_pos = make_pair(x, y);

            file >> rd->earliest_start >> rd->end;

            result.push(rd);
            ++index;
        }

        file.close();
    }

    return result;
}
