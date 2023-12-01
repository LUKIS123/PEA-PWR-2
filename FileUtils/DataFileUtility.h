#ifndef PEA_PWR_2_DATAFILEUTILITY_H
#define PEA_PWR_2_DATAFILEUTILITY_H

#include "iostream"
#include "vector"

class DataFileUtility {
public:
    static bool saveAutomaticTestResults(const std::string &FileName, const std::vector<double> &us,
                                         const std::vector<double> &ms, const std::vector<double> &s,
                                         const std::string &headline);

    static bool saveResultPath(const std::string &FileName, const std::vector<int> &path);

    static std::vector<int> readPathFromFile(const std::string &FileName);

};

#endif //PEA_PWR_2_DATAFILEUTILITY_H
