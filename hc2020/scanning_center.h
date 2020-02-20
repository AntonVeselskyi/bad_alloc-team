#pragma once

#include <list>
#include "entities.h"

using std::list;


class ScanningCenter {
private:
    list<Lib *> &libraries;
    list<Lib *> processed_libraries;

    Lib *sign_up_library;
    int days_to_sign_up_end;

    inline void sign_in_process() {
        if (!days_to_sign_up_end) {
            // Add library to list of scanning libraries
            if (sign_up_library != nullptr) {
                processed_libraries.push_back(sign_up_library);
            }

            // There are more libraries to sing up
            if (!libraries.empty()) {
                sign_up_library = libraries.front();
                libraries.pop_front();
                days_to_sign_up_end = sign_up_library->sign_length;
            }
        }

        // Should decrement only in case when sign_up_library not null
        if (!days_to_sign_up_end) {
            days_to_sign_up_end--;
        }
    }

public:
    explicit ScanningCenter(list<Lib *> &libraries) : libraries(libraries),
                                                      processed_libraries(),
                                                      sign_up_library(nullptr),
                                                      days_to_sign_up_end(0) {}

    void tick(int step) {
        sign_in_process();

        for (auto &l : processed_libraries) {
            // process libraries books
        }
    }

    list<Lib *> &get_processes_libraries() {
        return processed_libraries;
    }
};