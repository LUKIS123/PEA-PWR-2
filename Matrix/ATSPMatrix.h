#ifndef PEA_PWR_2_ATSPMATRIX_H
#define PEA_PWR_2_ATSPMATRIX_H

#include <iostream>
#include <vector>
#include <fstream>

class ATSPMatrix {
private:
    int **matrix = nullptr;
    int size = 0;

public:
    bool testing = false;
    bool exists = false;

    ATSPMatrix();

    virtual ~ATSPMatrix();

    int **getMatrix();

    int getSize();

    void loadFromFile(const std::string &filename);

    void displayMatrix();

    void calculatePathCost(const std::vector<int> &path);

private:
    void clearData();
};


#endif //PEA_PWR_2_ATSPMATRIX_H
