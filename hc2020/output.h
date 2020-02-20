#include <fstream>
#include <sstream>
#include <string>

using std::ofstream;
using std::stringstream;
using std::string;


class FileOutput
{
    ofstream ofs;

public:
    FileOutput(string filename): ofs(filename){}
    ~FileOutput(){ofs.close();}
    
    template<class... Args>
    void write_line(Args... args)
    {
        if (!ofs.is_open())
            return;

        size_t el_num_to_write =  sizeof... (args);
        for (auto arg: {args...})
        {
            //for the last one -- add endl
            if(!--el_num_to_write)
                ofs << arg << endl;
            else
                ofs << arg << " ";
        }
    }
};
