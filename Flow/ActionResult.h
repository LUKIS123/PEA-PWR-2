#ifndef PEA_PWR_2_ACTIONRESULT_H
#define PEA_PWR_2_ACTIONRESULT_H

class ActionResult {
public:
    enum mainMenu {
        END = 0,
        LOAD_DATA = 1,
        DISPLAY_DATA_BUFFER = 2,
        RUN_TESTS = 3,
        BACK_TO_MENU = 6
    };

    enum automaticTestsMenu {
        END_TEST = 0,
        MENU_TEST = 1,
        SET_TEST_COUNT = 2,
    };
};

#endif //PEA_PWR_2_ACTIONRESULT_H