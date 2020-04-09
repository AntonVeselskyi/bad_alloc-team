#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct Matrix
{
    vector<vector<unsigned>> _m;
    unsigned _trace = 0, _rrows = 0, _rcolumns = 0;


    void read_matrix(unsigned N)
    {
        _m.resize(N);
        for(unsigned i = 0; i < N; ++i)
        {
            _m[i].resize(N);
            for(unsigned val, j = 0; j < N; ++j)
            {
                cin >> val;
                _m[i][j] = val;
            }
        }
    }
    
    void compute()
    {

        for(unsigned i = 0; i < _m.size(); ++i)
        {
            //trace
            _trace += _m[i][i];
        
            //_rrows
            vector<unsigned> unique_row(_m[i].begin(), _m[i].end());
            sort(unique_row.begin(), unique_row.end());
            _rrows += unique(unique_row.begin(), unique_row.end()) != unique_row.end();

            //columns
            vector<unsigned> unique_column(_m.size());
            for(unsigned j = 0; j < _m.size(); ++j)
                unique_column[j] = _m[j][i];
            sort(unique_column.begin(), unique_column.end());
            _rcolumns += unique(unique_column.begin(), unique_column.end()) != unique_column.end();


        }
        
    }
};

int main()
{
    unsigned T=0;
    cin >> T;
    
    vector<Matrix> Ms(T);

    for(unsigned N,i = 0; i < T; ++i)
    {
        cin >> N;
        Ms[i].read_matrix(N);
        Ms[i].compute();
    }
    for(unsigned N,i = 0; i < T; ++i)
    {
        cout << "Case #" << i+1 << ": " 
          << Ms[i]._trace << " " << Ms[i]._rrows << " " 
          << Ms[i]._rcolumns << endl;
    }
    
}