#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

//digit char to int 
inline int dctoi(char ch){return int(ch - '0');}

struct DepthTestcase
{
    string input, output;

    void insert_parenthesis(unsigned index,  unsigned number)
    {
        output.insert(index, string(number,'('));
        output.insert(index+1+number, string(number,')'));
    }

    //return true if something was deleted
    bool delete_obsolete_parenthesis()
    {
        bool res = false;
        for(int i = 0; i < output.size(); ++i)
        {
            if(output[i] == ')'  && i != output.size()-1 && output[i+1] == '(' )
            {
                output.erase(i,2);
                res = true;
            }
        }
        return res;
    }

    string process()
    {
        output = input;

        //add parenthesis everywhere as many as number
        for(int i = 0; i < output.size();)
        {
            unsigned current_number = dctoi(output[i]);
            insert_parenthesis(i, current_number);
            i+= current_number ? current_number*2 + 1 : 1 /*case for 0*/;
        }


        //remove )( pairs
        while(delete_obsolete_parenthesis());

        return output;
    }
};

int main()
{
    unsigned T=0;
    cin >> T;

    vector<DepthTestcase> DTs(T);

    for(unsigned i = 0; i < T; ++i)
        cin >> DTs[i].input;

    for(unsigned i = 0; i < T; ++i)
        cout << "Case #" << i+1 << ": " << DTs[i].process() << endl;


}