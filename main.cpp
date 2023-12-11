#include <iostream>
#include <random>
#include "./Flow/AppController.h"

int main() {
    srand(time(NULL));
    auto *controller = new AppController();
    controller->mainIndex();
    delete controller;
    return 0;
}
