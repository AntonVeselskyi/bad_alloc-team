#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "entities.h"

using std::ofstream;
using std::stringstream;
using std::string;


class FileOutput {
    ofstream ofs;

public:
    explicit FileOutput(const string &filename) : ofs(filename) {}

    ~FileOutput() { ofs.close(); }

    template<class... Args>
    void write_line(Args... args) {
        if (!ofs.is_open())
            return;

        size_t el_num_to_write = sizeof... (args);
        auto dummy = {(ofs << args << (--el_num_to_write ? ' ' : '\n'), 0)...};
    }

    template<typename T>
    void write(T &v) {
        ofs << v;
    }

    void print_result(vector<Intersection> &intersections, StreetIndex &street_index) {
        intersections.erase(
                std::remove_if(
                        intersections.begin(),
                        intersections.end(),
                        [](Intersection &a) { return a.schedule.empty(); }
                ),
                intersections.end()
        );

        write_line(intersections.size());

        for (auto &intersection:intersections) {
            write_line(intersection.id);
            write_line(intersection.schedule.size());

            for (auto &street:intersection.schedule) {
                write_line(street_index[street.first], street.second);
            }
        }
    }
};

