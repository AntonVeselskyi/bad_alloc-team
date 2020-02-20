#include <iostream>
#include <list>
#include <vector>
#include <set>
#include "getline.h"
#include "output.h"

using namespace std;

struct Book
{
    int number;
    int award;
};

struct Lib
{
    int sign_lenth, books_per_day, book_num; 
    std::set<Book> book_set;
};


int main(int argc, char *argv[])
{
    //GET INPUT
    FileParser parser(argv[1]);
    int booksCount,
        libCount,
        days;
    vector<Book> global_books;

    parser.get_next_line(booksCount, libCount, days);

    cout << booksCount << libCount << days << endl;

     for(int i = 0; i < booksCount; ++i)
     {
         int award;
         parser.get_next_line(award);
         global_books.emplace_back(Book{i,award});
     }

    std::list<Lib> global_libs;
    for(int i = 0; i < libCount; ++i)
     {
         int award;
         //parser.get_next_line(award);
         //global_books.emplace_back(Book{i,award});
     }

    cout << endl;
    for(auto u : global_books)
        cout << u.number << " " <<u.award << endl;

    // //PROCESS INPUT


    // //WRITE RESULTS TO FILE
    // int res1 = 200, res2 = 99;
    // float res3 = 2.2;
    // auto res_vec = {"cool", "stuff"};
    
    // FileOutput output(string(argv[1])+"_res");
    // output.write_line(res1, res2, res3);
    // for(auto el: res_vec)
    //     output.write_line(el);

}