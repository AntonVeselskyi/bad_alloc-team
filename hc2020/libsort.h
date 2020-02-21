//
// Created by Borys on 20.02.2020.
//

#pragma once
#include "entities.h"

#include <numeric>
#include <list>
//#include <iostream>
#include <algorithm>

long long lib_score(list<Lib>& libs, int days_left)
{
    vector<int> AVE;
    //remove books that is scanned
    for (Lib &lib: libs)
    {
        std::remove_if(lib.book_set.begin(),lib.book_set.end(), [](Book *b){ return !b->is_not_scanned;});
        if(lib.book_set.empty())
            libs.remove(lib);
    }

    //average sign_length
    for (Lib &lib: libs)
        AVE.emplace_back(lib.sign_length);
    double AS = std::accumulate(AVE.begin(), AVE.end(), 0.0) / AVE.size();

    //average book by day coolness


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

            if (!book->reserved)
            {
                lib.j_score += book->award;
                books_to_scan--;
            }
        }
    
        //if(scanned_books == lib.book_set.size())
        //    libs.remove(lib);
    
        // std::cout << std::endl << "! SCORE "  <<lib.j_score
        //  << " \tNUM OF BOOKS " << lib.book_set.size() << " SIGNING  " <<
        //  lib.sign_length << "  BOOKS_BERDAY "<<lib.books_per_day << "\n";
        
        
        //lib.j_score*= (lib.book_set.size()-scanned_books);
        //std::cout << "+ new score" << lib.j_score;

        lib.j_score/= (lib.sign_length/AS);
        //std::cout << "\n+ newer score== " << lib.j_score << " with coof: "<< lib.sign_length/AS <<"\n" <<std::flush;
        
    }
    libs.sort();
}
