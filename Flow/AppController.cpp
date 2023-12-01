#include "AppController.h"

AppController::AppController() {
    matrix = new ATSPMatrix();
    annealing = new SimulatedAnnealing();
    tabuSearch = new TabuSearch();
}

AppController::~AppController() {
    clearMemory();
}

void AppController::clearMemory() {
    delete matrix;
    delete annealing;
    delete tabuSearch;
}

void AppController::mainIndex() {
    ActionResult::mainMenu status = ActionResult::BACK_TO_MENU;
    while (status != ActionResult::END) {
        switch (status) {
            case ActionResult::BACK_TO_MENU:
                status = ConsoleView::mainMenu();
                break;
            case ActionResult::LOAD_DATA:
                loadDataFile();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::DISPLAY_DATA_BUFFER:
                system("CLS");
                matrix->displayMatrix();
                system("PAUSE");
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::SET_TIMEOUT:
                setTimeout();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::SET_ALPHA_FACTOR:
                setAlphaFactor();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::RUN_ANNEALING:
                runSimulatedAnnealing();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::RUN_TABU_SEARCH:
                runTabuSearch();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::RUN_TESTS:
                testsMenu();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::DISPLAY_LATEST_RESULT:
                displayLatestResults();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::READ_AND_CALCULATE_SAVED_PATH:
                readPathAndDisplayCalculatedCost();
                status = ActionResult::BACK_TO_MENU;
                break;
            case ActionResult::END:
                break;
        }
    }
    std::cout << "Exiting Application..." << std::endl;
}

void AppController::loadDataFile() {
    std::string fileName;
    std::cout << "Place .atsp file in executable folder and enter file name (WITHOUT .atsp):" << std::endl;
    std::cin >> fileName;
    matrix->loadFromFile(fileName);
    system("PAUSE");
}

void AppController::setTimeout() {
    std::cout << "Set timeout [s]: ";
    std::cin >> timeoutSeconds;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> timeoutSeconds;
    }
    if (timeoutSeconds <= 0) {
        std::cout << "Wrong input!";
        timeoutSeconds = 120;
        system("PAUSE");
    }
}

void AppController::setAlphaFactor() {
    std::cout << "Set alpha (1 > a > 0): ";
    std::cin >> alphaFactor;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a DECIMAL: ";
        std::cin >> alphaFactor;
    }
    if (alphaFactor >= 1.0 || alphaFactor <= 0.0) {
        std::cout << "Wrong input!";
        alphaFactor = 0.99;
        system("PAUSE");
    }
}

void AppController::runSimulatedAnnealing() {
    if (!matrix->exists) {
        std::cout << "MATRIX IS EMPTY" << std::endl;
        system("PAUSE");
        return;
    }
    long long start = Timer::read_QPC();
    annealing->mainFun(matrix, alphaFactor, timeoutSeconds);
    long long end = Timer::read_QPC();
    annealing->displayLatestResults();
    latestTimerResult = Timer::getMicroSecondsElapsed(start, end);
    latestRun = LatestAlgorithm::SA;

    std::cout << "Timer: " << latestTimerResult << " us" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000 << " ms" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000000 << " s" << std::endl;
    DataFileUtility::saveResultPath(resultPathFileName, annealing->bestPath);
    system("PAUSE");
}

void AppController::runTabuSearch() {
    if (!matrix->exists) {
        std::cout << "MATRIX IS EMPTY" << std::endl;
        system("PAUSE");
        return;
    }
    long long start = Timer::read_QPC();
    tabuSearch->mainFun(matrix, timeoutSeconds);
    long long end = Timer::read_QPC();
    tabuSearch->displayLatestResults();
    latestTimerResult = Timer::getMicroSecondsElapsed(start, end);
    latestRun = LatestAlgorithm::TABU;

    std::cout << "Timer: " << latestTimerResult << " us" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000 << " ms" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000000 << " s" << std::endl;
    DataFileUtility::saveResultPath(resultPathFileName, tabuSearch->bestPath);
    system("PAUSE");
}

void AppController::displayLatestResults() {
    std::cout << "algorithm: ";
    switch (latestRun) {
        case SA:
            std::cout << algorithmTypes[0] << std::endl;
            break;
        case TABU:
            std::cout << algorithmTypes[1] << std::endl;
            break;
        default:
            return;
    }

    if (latestRun == LatestAlgorithm::SA) {
        annealing->displayLatestResults();
    }
    if (latestRun == LatestAlgorithm::TABU) {
        tabuSearch->displayLatestResults();
    }
    std::cout << "Timer: " << latestTimerResult << " us" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000 << " ms" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000000 << " s" << std::endl;
    system("PAUSE");
}

void AppController::readPathAndDisplayCalculatedCost() {
    auto pathVector = DataFileUtility::readPathFromFile(resultPathFileName);
    matrix->calculatePathCost(pathVector);
    system("PAUSE");
}

void AppController::testsMenu() {
    system("CLS");
    std::cout << "AUTOMATIC TESTS Initialization..." << std::endl;
    std::cout << std::endl << "Set number of tests..." << std::endl;
    std::cout << "Tests: ";
    std::cin >> testNumber;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> testNumber;
    }

    ActionResult::automaticTestsMenu status = ActionResult::MENU_TEST;
    while (status != ActionResult::END_TEST) {
        switch (status) {
            case ActionResult::MENU_TEST:
                status = ConsoleView::automaticTestsMenu();
                break;
            case ActionResult::TEST_SA:
                testSimulatedAnnealing();
                status = ActionResult::MENU_TEST;
                break;
            case ActionResult::TEST_TS:
                testTabuSearch();
                status = ActionResult::MENU_TEST;
                break;
            case ActionResult::END_TEST:
                break;
        }
    }
}

void AppController::testSimulatedAnnealing() {
    std::string fileName = "simulated_annealing_tests.csv";
    std::string bestResultPathFileName = "simulated_annealing_tests_bestpath";

    std::string cols = "us,ms,s";
    std::vector<double> resultsUS;
    std::vector<double> resultsMS;
    std::vector<double> resultsS;

    int bestCost = INT_MAX;
    std::vector<int> bestPath;

    long long int start, end;
    double results;
    for (int i = 0; i < testNumber; i++) {
        start = Timer::read_QPC();
        annealing->mainFun(matrix, alphaFactor, timeoutSeconds);
        end = Timer::read_QPC();

        results = Timer::getMicroSecondsElapsed(start, end);
        resultsUS.push_back(results);
        resultsMS.push_back(results / 1000);
        resultsS.push_back(results / 1000000);

        if (annealing->bestCost <= bestCost) {
            bestCost = annealing->bestCost;
            bestPath = annealing->bestPath;
        }
    }

    DataFileUtility::saveAutomaticTestResults(fileName, resultsUS, resultsMS, resultsS, cols);
    DataFileUtility::saveResultPath(bestResultPathFileName, bestPath);
    std::cout << "Done!" << std::endl;
    system("PAUSE");
}

void AppController::testTabuSearch() {
    std::string fileName = "tabu_search_tests.csv";
    std::string bestResultPathFileName = "tabu_search_tests_bestpath";

    std::string cols = "us,ms,s";
    std::vector<double> resultsUS;
    std::vector<double> resultsMS;
    std::vector<double> resultsS;

    int bestCost = INT_MAX;
    std::vector<int> bestPath;

    long long int start, end;
    double results;
    for (int i = 0; i < testNumber; i++) {
        start = Timer::read_QPC();
        tabuSearch->mainFun(matrix, timeoutSeconds);
        end = Timer::read_QPC();

        results = Timer::getMicroSecondsElapsed(start, end);
        resultsUS.push_back(results);
        resultsMS.push_back(results / 1000);
        resultsS.push_back(results / 1000000);

        if (tabuSearch->bestCost <= bestCost) {
            bestCost = tabuSearch->bestCost;
            bestPath = tabuSearch->bestPath;
        }
    }

    DataFileUtility::saveAutomaticTestResults(fileName, resultsUS, resultsMS, resultsS, cols);
    DataFileUtility::saveResultPath(bestResultPathFileName, bestPath);
    std::cout << "Done!" << std::endl;
    system("PAUSE");
}
