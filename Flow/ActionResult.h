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
        SET_TS_PARAMS = 6,
        RUN_TABU_SEARCH = 7,
        RUN_TESTS = 8,
        BACK_TO_MENU = 9,
        DISPLAY_LATEST_RESULT
    };

    enum automaticTestsMenu {
        END_TEST = 0,
        MENU_TEST = 1,
        SET_TEST_COUNT = 2,
    };
};

#endif //PEA_PWR_2_ACTIONRESULT_H