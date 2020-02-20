#pragma once
#include <string>
#include <fstream>
#include <utility>
#include "getline.h"

using namespace std;
class FileParser
{
    private:
    ifstream ifs;
    public:
    FileParser(string filename): ifs(filename){}
    ~FileParser(){ifs.close();}

    template<typename ...Args>
    void get_next_line(Args &...args)
    {
        if (!ifs.is_open())
            return;

        //sizeof... -- Returns the number of elements in a parameter pack.
        //we will apply the action in () for every element
        //and return 0 for dummy
        //int dummy[sizeof...(args)]
        auto dummy = {(ifs >> args,0)...};
    }

};