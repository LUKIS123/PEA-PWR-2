#ifndef PEA_PWR_2_APPCONTROLLER_H
#define PEA_PWR_2_APPCONTROLLER_H

#include <iostream>
#include <limits>
#include <cmath>
#include "./ActionResult.h"
#include "./ConsoleView.h"
#include "./LatestAlgorithmRan.h"
#include "../Matrix/ATSPMatrix.h"
#include "../MeasureTime/Timer.h"
#include "../Solutions/SimulatedAnnealing.h"
#include "../Solutions/TabuSearch.h"

class AppController {
private:
    ATSPMatrix *matrix = nullptr;
    SimulatedAnnealing *annealing = nullptr;
    TabuSearch *tabuSearch = nullptr;

    std::string algorithmTypes[2] = {
            "SIMULATED ANNEALING",
            "TABU SEARCH"
    };

    LatestAlgorithm latestRun = LatestAlgorithm::NONE;
    double latestTimerResult = 0.0;

    // SA
    double alphaFactor = 0.99;

    // TABU SEARCH
    int tabuMaxIterations = 1000000;
    int tabuIterationsCount = 100;

    // SHARED
    int timeoutSeconds = 120;

public:
    AppController();

    virtual ~AppController();

    void clearMemory();

    void mainIndex();

    void loadDataFile();

    void setTimeout();

    void setAlphaFactor();

    void runSimulatedAnnealing();

    void runTabuSearch();

    void testsMenu();

    void displayLatestResults();
};


#endif //PEA_PWR_2_APPCONTROLLER_H
