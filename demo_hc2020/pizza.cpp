#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int arc, char* argv[])
{
    int target=0, type_num=0;
    vector<int> pizzas;

    ifstream ifs (argv[1]);
    if (ifs.is_open())
    {
        ifs >> target >> type_num;
        //cout << target <<" "<< type_num << endl;
        for (int i;type_num--;)
        {
            ifs >>i;
            pizzas.push_back(i);
        }

        //for(auto g : pizzas)
        //   cout << g <<" ";

        ifs.close();
    }

    int target_left = target;
    vector<int> good_indxs;
    auto start=pizzas.begin(), middle=pizzas.begin()+pizzas.size()/2, end = pizzas.end();
    while(1)
    {
        //use binary search
        int left = std::accumulate(start, middle, 0),
            right = std::accumulate(middle, end, 0);

        if (right <= target)
        {
            target_left-=right;
            for(auto i = middle; i != end; i++)
                good_indxs.push_back(i-pizzas.begin());
            break;
        }
        else
        {
            start = middle;
            middle = start + (end-start)/2;
        }
    }

    while (middle-- != pizzas.begin() && target_left)
    {
        if(*middle <= target_left)
        {
            good_indxs.push_back(middle-pizzas.begin());
            target_left -= *middle;
        }
    }

    std::sort(good_indxs.begin(), good_indxs.end());
    
    //result
    //cout << endl << endl;
    //for(auto g : good_indxs)
    //    cout << g <<" ";

    std::ofstream ofs ("res.txt", std::ofstream::out);

    ofs << good_indxs.size() << endl;
    for(auto g : good_indxs)
        ofs << g <<" ";
    ofs.close();
}
