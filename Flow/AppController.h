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
#include "../FileUtils/DataFileUtility.h"
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
    std::string resultPathFileName = "latest_result_path";
    int testNumber = 10;

    LatestAlgorithm latestRun = LatestAlgorithm::NONE;
    double latestTimerResult = 0.0;

    // SA PARAMS
    double alphaFactor = 0.99;

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

    void readPathAndDisplayCalculatedCost();

    void testSimulatedAnnealing();

    void testTabuSearch();
};


#endif //PEA_PWR_2_APPCONTROLLER_H
