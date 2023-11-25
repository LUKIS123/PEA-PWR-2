#include <iostream>
#include <random>
#include "./Flow/AppController.h"

int main() {

//    ATSPMatrix *matrix = new ATSPMatrix();
//    //matrix->loadFromFile("../Resources/br17");
//    matrix->loadFromFile("../Resources/ft53");
//
//
//    SimulatedAnnealing *annealing = new SimulatedAnnealing();
//    annealing->mainFun(matrix, 0.99, 120);
//    system("PAUSE");
//    return 0;

    srand(time(NULL));
    auto *controller = new AppController();
    controller->mainIndex();
    delete controller;
    return 0;
}

/*
 * cost: 39
 * path: 15, 14, 5, 6, 4, 3, 16, 7, 8, 11, 0, 13, 2, 10, 1, 12, 9, 15,
 *
 * cost: 39
path: 11, 0, 2, 13, 12, 10, 9, 1, 14, 6, 5, 15, 3, 4, 7, 16, 8, 11,

 cost: 39
path: 0, 13, 2, 9, 12, 1, 10, 5, 15, 6, 14, 3, 4, 16, 7, 8, 11, 0,
*/