#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct LatinMatrixGen
{
    vector<vector<unsigned>> _m;
    unsigned _desired_trace = 0, _size=0;
    
    template<typename T>
    void shift_right(T a, T b)
    {
        std::rotate(a, a + 1, b);
    }

    bool shuffle_breakout(vector<vector<unsigned>*> &matrix)
    {
        //shuffle breaker
        for(int i = 0; i < _size; ++i)
        {
            shift_right(matrix.begin(), matrix.end());
            for(int k = 1; k < _size; ++k)
            {
                for(int j = 0; j<_size-k; ++j)
                shift_right(matrix.begin()+k, matrix.end());

                if(count_trace(matrix) == _desired_trace)
                {
                    save_matrix(matrix);
                    return true;
                }
                else if(count_2nd_trace(matrix) == _desired_trace)
                {
                    save_matrix(matrix);
                    swap_diagonals();
                    return true;
                }
            }

        }

        return false;
    }

    void save_matrix(vector<vector<unsigned>*> &matrix)
    {
        _m.resize(_size);
        for(int i = 0; i < _size; ++i)
        {
            _m[i].resize(_size);
            _m[i] = *matrix[i];
        }
    }

    void swap_diagonals()
    {
        for (int i=0;i<_size/2;i++) 
            for (int j=i;j<_size-i-1;j++) 
            { 
                    int temp=_m[i][j]; 
                    _m[i][j]=_m[_size-1-j][i]; 
                    _m[_size-1-j][i]=_m[_size-1-i][_size-1-j]; 
                    _m[_size-1-i][_size-1-j]=_m[j][_size-1-i]; 
                    _m[j][_size-1-i]=temp; 
            }
    }

    void free_matrix_ptrs(vector<vector<unsigned>*> &matrix)
    {
        for(int i =0; i < 0; ++i)
            delete matrix[i];
    }


    bool generate()
    {
        if(_size*_size < _desired_trace && _size > _desired_trace)
            return false;

        //alloc matrix
        vector<vector<unsigned>*> matrix(_size);
        //I
        for(int i = 0; i < _size; ++i)
        {
            matrix[i] = new vector<unsigned>(_size);
            for(int j = 0; j < _size; ++j)
                (*matrix[i])[j] = (i+j)%(_size) + 1;
        }
        bool res =  shuffle_breakout(matrix);

        //II
        if(!res)
        {
            for(int i = 0; i < _size; ++i)
                for(int j = 0; j < _size+1; j+=2)
                {
                    (*matrix[i])[j] = (i+j)%(_size) + 1;
                    if(j < _size)
                    (*matrix[i])[j+1] = (_size-1-(i+j))%(_size) + 1;
                }
        }
        res =  shuffle_breakout(matrix);

        //II.5
        if(!res)
        {
            for(int i = 0; i < _size; ++i)
            {
                if(i == 0)
                for(int j = 0; j < _size+1; j+=2)
                {
                    (*matrix[i])[j] = (i+j)%(_size) + 1;
                    if(j < _size)
                    (*matrix[i])[j+1] = (_size-1-(i+j))%(_size) + 1;
                }
                else
                {
                    auto new_row = (*matrix[i-1]);
                    std::rotate(new_row.begin(), new_row.begin()+1+(1*(i%2)), new_row.end());
                    (*matrix[i]) = std::move(new_row);                    
                }
            }
        }
        res =  shuffle_breakout(matrix);


        //II.6
        if(!res)
        {
            for(int i = 0; i < _size; ++i)
            {
                if(i == 0)
                for(int j = 0, k=0; j < _size+1; j+=2, k++)
                {
                    (*matrix[i])[j] = (i+k)%(_size) + 1;
                    if(j < _size)
                    (*matrix[i])[j+1] = (_size-1-(i+k))%(_size) + 1;
                }
                else
                {
                    auto new_row = (*matrix[i-1]);
                    std::rotate(new_row.begin(), new_row.begin()+1+(1*(i%2)), new_row.end());
                    (*matrix[i]) = std::move(new_row);                    
                }
            }

            // cout <<"SAMPLE\n";
            // for(unsigned i = 0; i < _size; ++i)
            // {
            //     for(unsigned j = 0; j < _size; ++j)
            //     {
            //         cout << (*matrix[i])[j];
            //         if(j != _size-1)
            //             cout << ' ';
            //     }
            //     cout << endl;
            // }
        }
        res =  shuffle_breakout(matrix);

        //III
        if(!res && !(_size%2))
        {

            for(int i = 0; i < _size; ++i)
            {
                if(i == 0)
                    for(int j = 0, k =0; j < _size; j+=2, ++k)
                    {
                        (*matrix[i])[j] = (_size-1-(i+k))%(_size) + 1;
                        (*matrix[i])[_size-1-j] = (i+k)%(_size) + 1;
                    }
                else
                {
                    auto new_row = (*matrix[i-1]);
                    std::rotate(new_row.begin(), new_row.begin()+1, new_row.end());
                    (*matrix[i]) = std::move(new_row);                    
                }

            }
        }
        res =  shuffle_breakout(matrix);

        //IV
        if(!res)
        {

            for(int i = 0; i < _size; ++i)
            {
                    for(int j = 0, k =0; j < _size/2; k+=2, ++j)
                    {
                        (*matrix[i])[j] = (i+k)%(_size) + 1;
                        if(j < _size)
                        (*matrix[i])[_size-1-j] = (i+k+1)%(_size) + 1;
                    }
            }
        }
        res =  shuffle_breakout(matrix);

        //V
        if(!res)
        {

            for(int i = 0; i < _size; ++i)
            {
                if(i == 0)
                    for(int j = 0, k =0; j < _size/2; k+=2, ++j)
                    {
                        (*matrix[i])[j] = (i+k)%(_size) + 1;
                        if(j < _size)
                        (*matrix[i])[_size-1-j] = (i+k+1)%(_size) + 1;
                    }
                else
                {
                    auto new_row = (*matrix[i-1]);
                    std::rotate(new_row.begin(), new_row.begin()+1+(1*(i%2)), new_row.end());
                    (*matrix[i]) = std::move(new_row);                    
                }
                
            }

        }
        res =  shuffle_breakout(matrix);


        free_matrix_ptrs(matrix);

        return res;   
    }


    unsigned count_trace(vector<vector<unsigned>*> &matrix)
    {
        unsigned trace = 0;
        for(unsigned i = 0; i < matrix.size(); ++i)
            trace += (*matrix[i])[i];

        return trace;
    }

    unsigned count_2nd_trace(vector<vector<unsigned>*> &matrix)
    {
        unsigned trace = 0;
        for(unsigned i = 0; i < matrix.size(); ++i)
            trace += (*matrix[i])[matrix.size()-1-i];

        return trace;
    }

    void print_matrix()
    {
        for(unsigned i = 0; i < _size; ++i)
        {
            for(unsigned j = 0; j < _size; ++j)
            {
                cout << _m[i][j];
                if(j != _size-1)
                    cout << ' ';
            }
            cout << endl;
        }
        
    }
};

int main()
{
    unsigned T=0;
    cin >> T;
    
    vector<LatinMatrixGen> Ms(T);

    for(unsigned i = 0; i < T; ++i)
    {
        cin >> Ms[i]._size >> Ms[i]._desired_trace;
    }
    for(unsigned i = 0; i < T; ++i)
    {
        bool res = Ms[i].generate();
        cout << "Case #" << i+1 << ": " << (res ? "POSSIBLE" : "IMPOSSIBLE") << endl;
        if(res)
            Ms[i].print_matrix();

    }
  
}