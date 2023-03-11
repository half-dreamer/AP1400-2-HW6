#ifndef Q2_H
#define Q2_H

#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

using std::cerr;
using std::endl;
using std::getline;
using std::ifstream;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;


namespace q2 
{
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };
    std::vector<Patient> read_file(std::string filename);
    void sort(std::vector<Patient>& patients);
};
// you should first declare q2, then the using will 
// recognize the variable inside the q2 namespace
using q2::Patient;

inline std::vector<Patient> q2::read_file(std::string filename)
{
    std::ifstream input(filename);
    if (! input.is_open()) {
        cerr << "can't open the input file" << endl;
    }
    string lineInput{};
    // bypass the first two lines;
    getline(input, lineInput);
    getline(input, lineInput);

    std::vector<Patient> patients{};

    while (getline(input, lineInput)) {
        stringstream sstream(lineInput);
        string name, surname, age, smokes, areaQ, alkhol;
        getline(sstream, name, ',');
        getline(sstream, surname, ',');
        getline(sstream, age, ',');
        getline(sstream, smokes, ',');
        getline(sstream, areaQ, ',');
        getline(sstream, alkhol);

        // process name
        size_t endPos = name.find_last_not_of(' ');
        name.erase(endPos + 1);

        int Age = stoi(age);
        int Smokes = stoi(smokes);
        int AreaQ = stoi(areaQ);
        int Alkhol = stoi(alkhol);
        Patient insertPat{name + ' ' + surname, static_cast<size_t>(Age),
                static_cast<size_t>(Smokes), static_cast<size_t>(AreaQ),
                static_cast<size_t>(Alkhol)};
        patients.push_back(insertPat);
    }
    return patients;
}
inline bool comparePoss(const Patient& a, const Patient& b) 
{
    size_t possOfa = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
    size_t possOfb = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
    return possOfa > possOfb;
}


inline void q2::sort(std::vector<Patient>& patients)
{
    std::sort(patients.begin(), patients.end(), comparePoss);
}

#endif //Q2_H