#ifndef PEA_PWR_2_CONSOLEVIEW_H
#define PEA_PWR_2_CONSOLEVIEW_H

#include <iostream>
#include <limits>
#include "ActionResult.h"

class ConsoleView {
public:
    ConsoleView() = default;

    virtual ~ConsoleView() = default;

    static ActionResult::mainMenu mainMenu();

    static ActionResult::automaticTestsMenu automaticTestsMenu();
};


#endif //PEA_PWR_2_CONSOLEVIEW_H
