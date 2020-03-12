#pragma once 

#include "entities.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, list<User*>> clusterize(vector<User> &people)
{
    map<string, list<User*>> res;
    for( auto &empl : people)
        res[empl.company].push_back(&empl);

    return res; 
}

