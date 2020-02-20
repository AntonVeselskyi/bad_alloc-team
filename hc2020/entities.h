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
    std::set<Book*> book_set;
    std::set<Book*> scanned_books;

    bool operator<(const Lib& rhs) const
    {
        return make_tuple(this->sign_length, this->j_score) > make_tuple(rhs.sign_length, rhs.j_score);
    } 
};