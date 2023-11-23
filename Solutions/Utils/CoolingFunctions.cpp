#include "CoolingFunctions.h"


double CoolingFunctions::updateWithLinearCooling(double temperature, const double &factor) {
    return temperature * factor;
}
