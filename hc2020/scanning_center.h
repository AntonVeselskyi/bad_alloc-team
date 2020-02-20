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
        if (!days_to_sign_up_end) {
            // Add library to list of scanning libraries
            if (!libraries.empty()) {
                processed_libraries.push_back(libraries.front());
                libraries.pop_front();
                lib_score(libraries);
            }

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
    explicit ScanningCenter(list<Lib> &libraries) : libraries(libraries),
                                                    processed_libraries(),
                                                    days_to_sign_up_end(0) {}

    void tick(int step) {
        sign_in_process();

        for (auto &l : processed_libraries) {
            if (l.book_set.empty()) {
                continue;
            }

            for (int i = 0; i < l.books_per_day && !l.book_set.empty(); i++) {
                auto b = *l.book_set.begin();
                b->is_scanned = true;
                l.book_set.erase(l.book_set.begin());
                l.scanned_books.insert(b);
            }
        }
    }

    list<Lib> &get_processes_libraries() {
        return processed_libraries;
    }
};