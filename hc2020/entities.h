#pragma once

#include <set>

using namespace std;

struct Book
{
    int number;
    int award;
     bool operator<(const Book& rhs) const
    {
        return this->award < rhs.award;
    }

};

struct Lib
{
    long long j_score = 0;
    int sign_length, books_per_day, book_num;
    std::set<Book*> book_set;
};