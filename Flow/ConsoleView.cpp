#include "ConsoleView.h"

ActionResult::mainMenu ConsoleView::mainMenu() {
    system("CLS");
    std::cout << "Menu: Choose from given options..." << std::endl;
    std::cout << "1 => Load input from file" << std::endl;
    std::cout << "2 => Display matrix" << std::endl;
    std::cout << "3 => Set timeout" << std::endl;
    std::cout << "4 => Set alpha factor" << std::endl;
    std::cout << "5 => Display latest result" << std::endl;
    std::cout << "6 => RUN: SIMULATED ANNEALING" << std::endl;
    std::cout << "7 => RUN: TABU SEARCH" << std::endl;
    std::cout << "8 => TESTS" << std::endl;
    std::cout << "0 => Exit" << std::endl;

    std::cout << "Choice: ";
    int next;
    std::cin >> next;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> next;
    }
    std::cout << std::endl;
    switch (next) {
        case 1:
            return ActionResult::LOAD_DATA;
        case 2:
            return ActionResult::DISPLAY_DATA_BUFFER;
        case 3:
            return ActionResult::SET_TIMEOUT;
        case 4:
            return ActionResult::SET_ALPHA_FACTOR;
        case 5:
            return ActionResult::DISPLAY_LATEST_RESULT;
        case 6:
            return ActionResult::RUN_ANNEALING;
        case 7:
            return ActionResult::RUN_TABU_SEARCH;
        case 8:
            return ActionResult::RUN_TESTS;
        case 0:
            return ActionResult::END;
        default:
            return ActionResult::BACK_TO_MENU;
    }
}

// TODO...
ActionResult::automaticTestsMenu ConsoleView::automaticTestsMenu() {
    system("CLS");
    std::cout << "AUTOMATIC TESTS: Choose from given options..." << std::endl;
    std::cout << "1 => Test BRUTE FORCE" << std::endl;
    std::cout << "2 => Test BRANCH AND BOUND" << std::endl;
    std::cout << "3 => Test DYNAMIC PROGRAMMING" << std::endl;
    std::cout << "4 => Change Test Count" << std::endl;
    std::cout << "0 => Exit" << std::endl;

    std::cout << "Choice: ";
    int next = 0;
    std::cin >> next;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Bad entry... Enter a NUMBER: ";
        std::cin >> next;
    }

    switch (next) {
        case 4:
            return ActionResult::automaticTestsMenu::SET_TEST_COUNT;
        case 0:
            return ActionResult::automaticTestsMenu::END_TEST;
        default:
            return ActionResult::automaticTestsMenu::MENU_TEST;
    }
}
