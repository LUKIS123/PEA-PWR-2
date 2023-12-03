#include "DataFileUtility.h"
#include "iostream"
#include "fstream"

using namespace std;

bool DataFileUtility::saveAutomaticTSTestResults(const std::string &FileName, const std::vector<double> &us,
                                                 const std::vector<double> &ms, const std::vector<double> &s,
                                                 const std::vector<int> &greedyCosts, const std::vector<int> &solCosts,
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
            auto gr_front = greedyCosts.begin();
            auto sol_front = solCosts.begin();
            for (; us_front != us.end(); ++us_front) {
                file << *us_front << "," << *ms_front << "," << *s_front << "," << *gr_front << "," << *sol_front
                     << endl;
                ++ms_front;
                ++s_front;
                ++gr_front;
                ++sol_front;
            }
            file.close();
        }
    } else {
        cout << "File error - OPEN" << endl;
        return false;
    }
    return true;
}

bool DataFileUtility::saveAutomaticSATestResults(const std::string &FileName, const std::vector<double> &us,
                                                 const std::vector<double> &ms,
                                                 const std::vector<double> &s,
                                                 const std::vector<int> &greedyCosts, const std::vector<int> &solCosts,
                                                 const std::vector<double> &endTemp, const std::vector<double> &exps,
                                                 double factor,
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
            auto gr_front = greedyCosts.begin();
            auto sol_front = solCosts.begin();
            auto endT_front = endTemp.begin();
            auto exps_front = exps.begin();

            for (; us_front != us.end(); ++us_front) {
                file << *us_front << "," << *ms_front << "," << *s_front << "," << *gr_front << "," << *sol_front << ","
                     << *endT_front << "," << *exps_front << "," << factor << endl;
                ++ms_front;
                ++s_front;
                ++gr_front;
                ++sol_front;
                ++endT_front;
                ++exps_front;
            }
            file.close();
        }
    } else {
        cout << "File error - OPEN" << endl;
        return false;
    }
    return true;
}

bool DataFileUtility::saveResultPath(const string &FileName, const vector<int> &path) {
    ofstream file;
    file.open(FileName + ".txt", ios::out);
    if (file.is_open()) {
        file << path.size() << endl << endl;
        if (file.fail()) {
            cout << "File error - SAVE HEADLINE" << endl;
            return false;
        } else {
            for (int it: path) {
                file << it << endl;
            }
            file.close();
        }
    } else {
        cout << "File error - OPEN" << endl;
        return false;
    }
    return true;
}

std::vector<int> DataFileUtility::readPathFromFile(const string &FileName) {
    int size;
    vector<int> path;

    ifstream file(FileName + ".txt");
    if (file.good()) {

        file >> size;
        path = vector<int>(size, 0);

        for (int i = 0; i < size; i++) {
            file >> path[i];
        }
        file.close();
    } else {
        cout << "File error - OPEN" << endl;
    }
    return path;
}
