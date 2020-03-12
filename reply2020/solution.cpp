#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <utility>
#include "getline.h"
#include "output.h"


int main(int argc, char *argv[]) {
    //GET INPUT
    FileParser parser(argv[1]);
    int booksCount,
            libCount,
            days;

    parser.get_next_line(booksCount, libCount, days);

    for (int i = 0; i < booksCount; ++i) {
        int award;
        parser.get_next_line(award);
        global_books.emplace_back(Book{i, award});
    }


    FileOutput output(string(argv[1])+"_res");
    output.write_line(res.size());

    for (auto it: res) {
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
