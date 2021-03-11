#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "entities.h"

using std::ofstream;
using std::stringstream;
using std::string;


class FileOutput
{
    ofstream ofs;

public:
    explicit FileOutput(const string &filename) : ofs(filename) {}

    ~FileOutput() { ofs.close(); }

    template<class... Args>
    void write_line(Args... args)
    {
        if (!ofs.is_open())
            return;

        size_t el_num_to_write = sizeof... (args);
        auto dummy = {(ofs << args << (--el_num_to_write ? ' ' : '\n'), 0)...};
    }

    template<typename T>
    void write(T &v)
    {
        ofs << v;
    }

    void print_result(vector<Antena> &&output_antennas = vector<Antena>())
    {
        write_line(output_antennas.size());
        for (auto antenna: output_antennas) {
            write_line(antenna.id, antenna.x, antenna.y);
        }
    }
};

