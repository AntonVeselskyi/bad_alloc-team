#pragma once

#include <set>
#include <tuple>

using namespace std;

struct Book
{
    int number;
    int award;
    bool is_not_scanned = true;

     bool operator<(const Book& rhs) const
    {
        return this->award > rhs.award;
    }

};

struct Lib
{
    long long j_score = 0;
    int sign_length, books_per_day, book_num, lib_id;
    std::list<Book*> book_set;
    std::list<Book*> scanned_books;

    bool operator<(const Lib& rhs) const
    {
        return this->j_score >  rhs.j_score;
    }

    bool operator==(const Lib& rhs) const
    {
        return this->lib_id == rhs.lib_id;
    }
};