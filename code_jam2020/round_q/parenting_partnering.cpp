#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <bitset>
using namespace std;

struct Activity
{
    //in minutes after midnight
    unsigned start, end, original_index;
    Activity *pre_overlap = nullptr, *post_overlap = nullptr;
    char responisble = ' ';

    bool operator<(const Activity& rhs) const
    {
        return this->start <  rhs.start;
    }
};

//Quick solution,
//I can afford to spend 3KB on the arrays
//when I have 1GB limit. :) (will share it between testcases to save memory)
//each array represent 'busyness' of preson,
//if 1 the minute is busy
bitset<1441> J_day, C_day;

struct PlanningTestcase
{
    vector<Activity> _activities;

    void discover_overlaps()
    {
        for(int i = 0; i < _activities.size(); ++i)
        {
            Activity &current = _activities[i];

            for(int j = 0; j < _activities.size(); ++j)
            {
                if(j == i) continue;

                if(_activities[j].start < current.start &&
                   _activities[j].end > current.start)
                   current.pre_overlap = &_activities[j];

                if(_activities[j].start < current.end &&
                   _activities[j].end > current.end)
                   current.post_overlap = &_activities[j];

            }
        }
    }

    //inclusive [start,end]
    bool is_timeslot_free(bitset<1441> *_day, unsigned start, unsigned end)
    {
        for(int i = start; i <= end; ++i)
            if((*_day)[i]) return false;
        //special case for 1 minute interval
        if(end == start-1)
            return !(*_day)[end] || !(*_day)[start];

        return true;
    }

    //return true if it is possible to fit this acticity
    bool fit_activity(Activity &act)
    {
        if(act.pre_overlap && act.pre_overlap->responisble != ' ')
            act.responisble = act.pre_overlap->responisble == 'J' ? 'C' : 'J';
        else if(act.post_overlap && act.post_overlap->responisble != ' ')
            act.responisble = act.post_overlap->responisble == 'J' ? 'C' : 'J';
        else
            act.responisble = 'J';

        bitset<1441> *_day = nullptr;
        if(act.responisble == 'J'
            && is_timeslot_free(&J_day,act.start+1,act.end-1))
         _day = &J_day;
        else if (is_timeslot_free(&C_day,act.start+1,act.end-1))
        {
            act.responisble = 'C';
            _day = &C_day;
        }
        else return false;

        for(int i = act.start; i <= act.end; ++i)
            (*_day)[i] = 1;

        return true;
    }

    string get_plan()
    {
        J_day.reset();
        C_day.reset();

        for(unsigned i = 0; i < _activities.size(); ++i)
            _activities[i].original_index = i;

        sort(_activities.begin(),_activities.end());
        discover_overlaps();

        for(auto& act : _activities)
            if(!fit_activity(act))
                return "IMPOSSIBLE";


        sort(_activities.begin(),_activities.end(),[](auto a, auto b){ return a.original_index<b.original_index;});
        string plan = "";
        for(auto& act : _activities)
            plan += act.responisble;

        return plan;
    }
};

int main()
{
    unsigned T=0;
    //number of testcases
    cin >> T;

    vector<PlanningTestcase> PTs(T);

    //read input
    for(unsigned i = 0; i < T; ++i)
    {
        unsigned N = 0;
        cin >> N;
        PTs[i]._activities.resize(N);
        for(auto& act : PTs[i]._activities)
            cin >> act.start >> act.end;

    }

    for(unsigned i = 0; i < T; ++i)
        cout << "Case #" << i+1 << ": " << PTs[i].get_plan() << endl;


}