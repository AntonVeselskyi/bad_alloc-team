#include <iostream>
#include <utility>
#include "getline.h"
#include "output.h"
#include "entities.h"


int main(int argc, char *argv[])
{
    FileParser parser(argv[1]);

    FileOutput output(string(argv[1]) + "_res");


    unsigned simulationDuration, numberOfIntersections,
            numberOfStreets, numberOfCars, finishBonus;

    parser.get_next_line(simulationDuration, numberOfIntersections,
                         numberOfStreets, numberOfCars, finishBonus);




    output.print_result();

}