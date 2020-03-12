#pragma once 

#include "entities.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, vector<User*>> clusterize(vector<User> &people)
{
    map<string, vector<User*>> res;
    for( auto &empl : people)
        res[empl.company].push_back(&empl);

    return res; 
}

