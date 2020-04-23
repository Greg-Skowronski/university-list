#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
#include <string>

class Student
{
private:
    string dni;
    string name;
    bool graduated;

public:
    string getDNI() { return dni; }
    void setDNI(string dni) { this->dni = dni; }
    string getName() { return name; }
    void setName(string name) { this->name = name; }
    bool getGraduated() { return graduated; }
    void setGraduated(bool graduated) { this->graduated = graduated; }
    Student(string, string, bool);
    Student() {}
    bool operator==(string);
};

Student::Student(string dni, string name, bool graduated)
{
    this->dni = dni;
    this->name = name;
    this->graduated = graduated;
}

bool Student::operator==(string dni)
{
    if (this->dni.compare(dni) == 0)
        return true;
    return false;
}

#endif