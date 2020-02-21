#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"
#include "scanning_center.h"
#include "libsort.h"


int main(int argc, char *argv[]) {
    //GET INPUT
    FileParser parser(argv[1]);
    int booksCount,
            libCount,
            days;
    vector<Book> global_books;

    parser.get_next_line(booksCount, libCount, days);

    //cout << booksCount << libCount << days << endl;

    for (int i = 0; i < booksCount; ++i) {
        int award;
        parser.get_next_line(award);
        global_books.emplace_back(Book{i, award});
    }

    std::list<Lib> global_libs;
    for (int i = 0; i < libCount; ++i) {
        Lib new_lib;
        new_lib.lib_id = i;
        parser.get_next_line(new_lib.book_num, new_lib.sign_length, new_lib.books_per_day);
        for (int j = 0, book_id; j < new_lib.book_num; ++j) {
            parser.get_next_line(book_id);
            new_lib.book_set.insert(&global_books[book_id]);
        }
        global_libs.emplace_back(std::move(new_lib));
    }

    //books
    //cout << endl;
    //for (auto u : global_books)
    //    cout << u.number << " " << u.award << endl;

    //libs
    //cout << endl << endl << endl;
    //for (auto u : global_libs) {
    //    cout << u.book_num << " " << u.sign_length << " " << u.books_per_day << endl;
        //for(for int i =0; i < u.book_num; ++i)
        //{

        //}
    //}

    //SORT LIBS
    list<Lib> sorted_libs = move(lib_sort(global_libs, days));
    //PROCESS LIBS IN SCAAN CENTER
    ScanningCenter scan_center(sorted_libs, days);
    for (unsigned step = 0; step < days; ++step) {
        scan_center.tick();
    }

    auto res = scan_center.get_processes_libraries();

    FileOutput output(string(argv[1])+"_res");
    output.write_line(res.size());

    for (const auto &it: res) {
        output.write_line(it.lib_id, it.scanned_books.size());
        for (auto book: it.scanned_books) {
            output.write(book->number);
            output.write(" ");
        }
        output.write("\n");
    }



    // //WRITE RESULTS TO FILE
    // int res1 = 200, res2 = 99;
    // float res3 = 2.2;
    // auto res_vec = {"cool", "stuff"};
    
    // FileOutput output(string(argv[1])+"_res");
    // output.write_line(res1, res2, res3);
    // for(auto el: res_vec)
    //     output.write_line(el);

}