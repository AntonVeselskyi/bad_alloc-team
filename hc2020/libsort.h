//
// Created by Borys on 20.02.2020.
//

#pragma once
#include "entities.h"

#include <numeric>
#include <list>

long long lib_score(list<Lib>& libs, int days_left)
{
    for (Lib &lib: libs)
    {
        for(Book *book:lib.book_set)
        {
            if (book->is_not_scanned)
            {
                lib.j_score += book->award;
            }
        }
        lib.j_score /= lib.books_per_day;
    }

    libs.sort();
}
