#pragma once

#include <algorithm>
#include "entities.h"
#incldue "islands.h"

void sort_list_by_coolness(vector<User*> &devs)
{
    for(auto &d_ptr : devs)
    {
        long long sum = 0;
        for(auto &other_ptr : devs)
        {
            if(other_ptr != d_ptr)
            sum += score(*other_ptr , *d_ptr);
        }
        d_ptr->avg_cluster_score = sum / (devs.size()-1);

    }
    devs.sort([](auto *a, auto *b){ return *a<*b;})
}

void sort_list_by_greed(vector<User*> &pms)
{
    pms.sort([](auto *a, auto *b){ return *a<*b;})
}



fit_on_island(Room &room, const Island &ilnd, vector<User*> &devs, vector<User*> &pms)
{
    sort_list_by_coolness(devs);
    sort_list_by_greed(pms);

    int num_of_pms_places = count_if(ilnd.start(), ilnd.end(), [&room](Pos &pos){return get_place(room, pos) == PM_FREE;}),
    num_of_devs_places = ilnd.size() - num_of_pms_places;

    for(auto pos : ilnd)
    {
        if(get_place(room, pos) == DEV_FREE)
        {
            auto &dev = devs.front();
            pm->pos = pos;
            pms.pop_front()
        }
        else
        {
            auto &pm = pms.front();
            pm->pos = pos;
            pms.pop_front()

        }
    }    
}