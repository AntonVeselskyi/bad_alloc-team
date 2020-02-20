//
// Created by Borys on 20.02.2020.
//

#pragma once
#include "entities.h"

#include <numeric>
#include <list>

long long lib_score(list<Lib>& libs, int days_left)
{
    vector<int> AVE;
    for (Lib &lib: libs)
        AVE.emplace_back(lib.sign_length);

    double AS = std::accumulate(AVE.begin(), AVE.end(), 0.0) / AVE.size();
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

            if (book->is_not_scanned)
            {
                lib.j_score += book->award;
                books_to_scan--;
            }
        }

        lib.j_score/=(lib.sign_length/AS);
    }
    libs.sort();
}
