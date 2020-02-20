#pragma once

#include <set>

using namespace std;

struct Book {
    int number;
    int award;
};

struct Lib {
    int sign_length, books_per_day, book_num;
    std::set<Book> book_set;
};