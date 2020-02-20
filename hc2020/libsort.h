//
// Created by Borys on 20.02.2020.
//


#include "entities.h"

#include <numeric>
#include <list>

long long lib_score(list<Lib>& libs)
{
    for (Lib &lib: libs)
    {
        for(Book *book:lib.book_set)
        {
            lib.j_score += book->award;
        }
        lib.j_score /= lib.books_per_day;
    }

    libs.sort();
}
