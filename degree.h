#ifndef DEGREE_H
#define DEGREE_H
using namespace std;
#include <string>
#include <vector>
#include "student.h"

class Degree
{
private:
    string name;
    vector<Student> all;
    int n;

public:
    string getName() { return name; }
    Student &getStudent(int i) { return all.at(i); }
    void removeStudent(int i)
    {
        all.erase(all.begin() + i);
        n--;
    }
    int getN() { return n; }
    Degree(string);
    Degree() { n = 0; }
    void operator+=(Student);
    bool operator==(string);
};

Degree::Degree(string name)
{
    this->name = name;
    n = 0;
}

void Degree::operator+=(Student student)
{
    all.push_back(student);
    n++;
}

bool Degree::operator==(string name)
{
    if (this->name.compare(name) == 0)
        return true;
    return false;
}

#endif