#ifndef PEA_PWR_2_COOLINGFUNCTIONS_H
#define PEA_PWR_2_COOLINGFUNCTIONS_H

#include "cmath"

class CoolingFunctions {

public:
    static double updateWithLinearCooling(double temperature, const double &factor);

    static double updateWithLogarithmicCooling(double temperature, const double &factor, int k);
};


#endif //PEA_PWR_2_COOLINGFUNCTIONS_H
