#ifndef UNIVERSITY_H
#define UNIVERSITY_H
using namespace std;
#include <string>
#include <vector>
#include "student.h"
#include "degree.h"

class University
{
private:
    vector<Degree> all;
    int n;

public:
    Degree &getDegree(int i) { return all.at(i); }
    void removeDegree(int i)
    {
        all.erase(all.begin() + i);
        n--;
    }
    int getN() { return n; }
    University() { n = 0; }
    void operator+=(Degree);
};

void University::operator+=(Degree degree)
{
    all.push_back(degree);
    n++;
}

#endif