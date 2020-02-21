#pragma once

#include <list>
#include "libsort.h"
#include "entities.h"

using std::list;


class ScanningCenter {
private:
    list<Lib> &libraries;
    list<Lib> processed_libraries;

    int days;
    int days_to_sign_up_end;

    inline void sign_in_process(int step) {
        if (!days_to_sign_up_end) {
            // Add library to list of scanning libraries
            if (!libraries.empty()) {
                processed_libraries.push_back(libraries.front());
                libraries.pop_front();
                lib_score(libraries, days - step);
            }

            // There are more libraries to sing up
            if (!libraries.empty()) {
                days_to_sign_up_end = libraries.front().sign_length;
                for(Book *b : libraries.front().book_set)
                {
                    b->reserved = true;
                }
            }
        }

        // Should decrement only in case when sign_up_library not null
        if (days_to_sign_up_end) {
            days_to_sign_up_end--;
        }
    }

public:
    explicit ScanningCenter(list<Lib> &libraries, int days) : libraries(libraries),
                                                              days(days),
                                                              processed_libraries(),
                                                              days_to_sign_up_end(0) {}

    void tick(int step) {
        sign_in_process(step);

        for (auto &l : processed_libraries) {
            if (l.book_set.empty()) {
                continue;
            }

            int scanned_book_per_day = 0;
            while (scanned_book_per_day < l.books_per_day && !l.book_set.empty()) {
                auto b = *l.book_set.begin();
                l.book_set.erase(l.book_set.begin());

                if (b->is_not_scanned) {
                    b->is_not_scanned = false;
                    l.scanned_books.push_back(b);
                    scanned_book_per_day++;
                }

            }
        }
    }

    list<Lib> &get_processes_libraries() {
        return processed_libraries;
    }
};