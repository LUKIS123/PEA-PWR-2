#ifndef PEA_PWR_2_ACTIONRESULT_H
#define PEA_PWR_2_ACTIONRESULT_H

class ActionResult {
public:
    enum mainMenu {
        END = 0,
        LOAD_DATA = 1,
        DISPLAY_DATA_BUFFER = 2,
        SET_TIMEOUT = 3,
        SET_ALPHA_FACTOR = 4,
        RUN_ANNEALING = 5,
        RUN_TABU_SEARCH = 6,
        RUN_TESTS = 7,
        BACK_TO_MENU = 8,
        DISPLAY_LATEST_RESULT = 9,
        READ_AND_CALCULATE_SAVED_PATH = 10,
    };

    enum automaticTestsMenu {
        END_TEST = 0,
        MENU_TEST = 1,
        TEST_SA = 2,
        TEST_TS = 3,
    };
};

#endif //PEA_PWR_2_ACTIONRESULT_H