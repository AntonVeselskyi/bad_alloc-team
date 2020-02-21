#pragma once

#include <list>
#include "libsort.h"
#include "entities.h"

using std::list;


class ScanningCenter {
private:
    list<Lib> &libraries;
    list<Lib> processed_libraries;

    int days_to_sign_up_end;

    inline void sign_in_process() {
        if (!days_to_sign_up_end && !libraries.empty()) {
            // Add library to list of scanning libraries
            processed_libraries.push_back(libraries.front());
            libraries.pop_front();

            // There are more libraries to sing up
            if (!libraries.empty()) {
                days_to_sign_up_end = libraries.front().sign_length;
            }
        }

        // Should decrement only in case when sign_up_library not null
        if (days_to_sign_up_end) {
            days_to_sign_up_end--;
        }
    }

public:
    explicit ScanningCenter(list<Lib> &libraries, int days) : libraries(libraries),
                                                              processed_libraries() {
        days_to_sign_up_end = libraries.front().sign_length;
    }

    void tick() {
        sign_in_process();

        for (auto &l : processed_libraries) {
            if (l.book_set.empty()) {
                continue;
            }

            int scanned_book_per_day = 0;
            while (scanned_book_per_day < l.books_per_day && !l.book_set.empty()) {
                auto b = *l.book_set.begin();
                l.book_set.erase(b);
                l.scanned_books.insert(b);
            }
        }
    }

    list<Lib> &get_processes_libraries() {
        return processed_libraries;
    }
};