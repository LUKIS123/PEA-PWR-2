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
// todo: dodac dodawanie pozostałych elementow tabu jesli spelniaja aspiracje
// dodac komentarze do TABU SEARCH