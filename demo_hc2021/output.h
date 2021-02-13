#include <fstream>
#include <sstream>
#include <string>

using std::ofstream;
using std::stringstream;
using std::string;


class FileOutput {
    ofstream ofs;

public:
    explicit FileOutput(const string &filename) : ofs(filename) {}

    ~FileOutput() { ofs.close(); }

    template<class... Args>
    void write_line(Args... args) {
        if (!ofs.is_open())
            return;

        size_t el_num_to_write = sizeof... (args);
        auto dummy = {(ofs << args << (--el_num_to_write ? ' ' : '\n'), 0)...};
    }

    template<typename T>
    void write(T &v) {
        ofs << v;
    }
};
