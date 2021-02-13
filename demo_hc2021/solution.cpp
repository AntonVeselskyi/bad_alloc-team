#include <iostream>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"

int main(int argc, char *argv[]) {
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");
    //Usage example
    //output.write_pizza_result(PizzaIndexes vector)
}