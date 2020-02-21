//
// Created by Borys on 20.02.2020.
//

#pragma once
#include "entities.h"

#include <numeric>
#include <list>

void lib_score(list<Lib> &libs, int days_left) {
    long long sign_up_days = 0;

    for (Lib &lib: libs)
        sign_up_days += lib.sign_length;

    double AS = sign_up_days / ((float) libs.size());
    for (Lib &lib: libs)
    {

        lib.j_score = 0;
        long long books_to_scan = (days_left - lib.sign_length) * lib.books_per_day;
        for(Book *book:lib.book_set)
        {
            if (books_to_scan <= 0)
            {
                break;
            }

            lib.j_score += book->award;
            books_to_scan--;
        }

        lib.j_score/=(lib.sign_length/AS);
    }
    libs.sort();
}

std::list<Lib> lib_sort(list<Lib> libs, int days) {
    int current_day = 0;
    list<Lib> libs_to_process;

    while (current_day < days && !libs.empty()) {
        lib_score(libs, days - current_day);

        auto lib = libs.front();
        libs.pop_front();

        libs_to_process.push_back(lib);
        current_day += lib.sign_length;

        for (auto &l : libs) {
            for (auto &b : lib.book_set) {
                l.book_set.erase(b);
            }
        }
    }

    return libs_to_process;
}
