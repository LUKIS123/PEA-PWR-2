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
            case ActionResult::SET_TS_PARAMS:
                setTSParams();
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
    system("PAUSE");
}

void AppController::setTSParams() {
    std::cout << "Set TS max iterations: ";
    std::cin >> tabuMaxIterations;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> tabuMaxIterations;
    }
    if (tabuMaxIterations <= 0) {
        std::cout << "Wrong input!";
        tabuMaxIterations = 1000000;
        system("PAUSE");
        return;
    }
    std::cout << "Set TS cadence: ";
    std::cin >> cadence;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> cadence;
    }
    if (cadence <= 0) {
        std::cout << "Wrong input!";
        cadence = 100;
        system("PAUSE");
        return;
    }
}

void AppController::runTabuSearch() {
    if (!matrix->exists) {
        std::cout << "MATRIX IS EMPTY" << std::endl;
        system("PAUSE");
        return;
    }
    long long start = Timer::read_QPC();
    tabuSearch->mainFun(matrix, cadence, tabuMaxIterations, timeoutSeconds);
    long long end = Timer::read_QPC();
    tabuSearch->displayLatestResults();
    latestTimerResult = Timer::getMicroSecondsElapsed(start, end);
    latestRun = LatestAlgorithm::TABU;

    std::cout << "Timer: " << latestTimerResult << " us" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000 << " ms" << std::endl;
    std::cout << "     : " << latestTimerResult / 1000000 << " s" << std::endl;
    system("PAUSE");
}

void AppController::testsMenu() {

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
            break;
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
