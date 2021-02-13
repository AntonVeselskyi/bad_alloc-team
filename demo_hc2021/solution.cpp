#include <iostream>
#include <utility>
#include "getline.h"
#include "output.h"


int main(int argc, char *argv[]) {
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");
}