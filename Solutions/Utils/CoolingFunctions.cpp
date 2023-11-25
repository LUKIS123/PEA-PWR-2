#include "CoolingFunctions.h"


double CoolingFunctions::updateWithLinearCooling(double temperature, const double &factor) {
    return temperature * factor;
}

double CoolingFunctions::updateWithLogarithmicCooling(double temperature, const double &factor, int k) {
    return temperature / (1 + factor * log(1 + k));
}
