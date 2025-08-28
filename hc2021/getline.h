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
    explicit FileParser(const string& filename): ifs(filename){}
    ~FileParser(){ifs.close();}

    template<typename ...Args>
    void get_next_line(Args &...args)
    {
        if (!ifs.is_open())
            return;

        //we will apply the action in () for every element
        //and return 0 for dummy
        auto dummy = {(ifs >> args,0)...};
    }

};
