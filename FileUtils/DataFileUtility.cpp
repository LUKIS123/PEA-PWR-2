#include "DataFileUtility.h"
#include "iostream"
#include "fstream"

using namespace std;

bool DataFileUtility::saveAutomaticTestResults(const std::string &FileName, const std::vector<double> &us,
                                               const std::vector<double> &ms, const std::vector<double> &s,
                                               const std::string &headline) {
    ofstream file;
    file.open(FileName, ios::out);
    if (file.is_open()) {
        file << headline << endl;
        if (file.fail()) {
            cout << "File error - SAVE HEADLINE" << endl;
            return false;
        } else {
            auto us_front = us.begin();
            auto ms_front = ms.begin();
            auto s_front = s.begin();
            for (; us_front != us.end(); ++us_front) {
                file << *us_front << "," << *ms_front << "," << *s_front << endl;
                ++ms_front;
                ++s_front;
            }
            file.close();
        }
    } else {
        cout << "File error - OPEN" << endl;
        return false;
    }
    return true;
}