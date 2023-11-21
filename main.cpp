#include <iostream>

#include "./Matrix/ATSPMatrix.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    ATSPMatrix *matrix = new ATSPMatrix();
    matrix->loadFromFile("../Resources/br17");
    matrix->displayMatrix();
    system("PAUSE");

    return 0;
}
