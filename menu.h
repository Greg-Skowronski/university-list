#ifndef MENU_H
#define MENU_H
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "student.h"
#include "degree.h"
#include "university.h"
#include "check.h"

class Menu
{
private:
    University uni;

public:
    void add();
    void eliminate();
    void list();
    void import();
    void start();
    void save();
};

void Menu::add()
{
    string degree, dni, name, graduated;
    int presence = 0;
    cout << "Enter name of the degree: ";
    do
    {
        getline(cin, degree);
    } while (degree_check(degree) != true);
    cout << "Enter DNI of the student: ";
    do
    {
        getline(cin, dni);
    } while (dni_check(dni) != true);
    cout << "Enter name of the student: ";
    do
    {
        getline(cin, name);
    } while (name_check(name) != true);
    cout << "Has the student graduated? (yes/no) ";
    do
    {
        getline(cin, graduated);
    } while (graduated_check(graduated) != true);
    //check if this degree exists
    for (int i = 0; i < uni.getN(); i++)
    {
        if (uni.getDegree(i) == degree)
        {
            cout << "The degree has been found!" << endl;
            //check if the student is there
            for (int j = 0; j < uni.getDegree(i).getN(); j++)
            {
                if (uni.getDegree(i).getStudent(j) == dni)
                {
                    cout << "The student has been updated!" << endl;
                    uni.getDegree(i).getStudent(j).setName(name);
                    uni.getDegree(i).getStudent(j).setGraduated(to_bool(graduated));
                    return;
                }
            }
        }
    }
    //check in how many degrees the student is rolled out
    for (int i = 0; i < uni.getN(); i++)
    {
        for (int j = 0; j < uni.getDegree(i).getN(); j++)
        {
            if (uni.getDegree(i).getStudent(j) == dni)
                presence++;
        }
    }
    if (presence < 2)
    {
        for (int i = 0; i < uni.getN(); i++)
        {
            if (uni.getDegree(i) == degree)
            {
                cout << "The degree has been found!" << endl;
                uni.getDegree(i) += Student(dni, name, to_bool(graduated));
                return;
            }
        }
        uni += Degree(degree);
        uni.getDegree(uni.getN() - 1) += Student(dni, name, to_bool(graduated));
    }
    else
    {
        cout << "The student cannot be rolled out in more than 2 degrees." << endl;
    }
}

void Menu::eliminate()
{
    for (int i = uni.getN()-1; i>=0; i--)
    {
        for (int j = uni.getDegree(i).getN()-1; j>=0 ; j--)
        {
            if (uni.getDegree(i).getStudent(j).getGraduated() == true)
            {
                uni.getDegree(i).removeStudent(j);
            }
        }
    }
    for (int i = uni.getN()-1; i>=0; i--)
    {
        if (uni.getDegree(i).getN() == 0)
        {
            uni.removeDegree(i);
        }
    }
}

void Menu::list()
{
    Student temp;
    int sum = 0;
    cout << endl
         << endl
         << endl
         << "Universidad de Alicante" << endl;
    for (int i = 0; i < uni.getN(); i++)
    {
        cout << endl
             << uni.getDegree(i).getName() << endl
             << "Number of students: " << uni.getDegree(i).getN() << endl;
        cout << left << setw(14) << "DNI" << setw(30) << "NAME" << setw(10) << "GRADUATED" << endl;
        for (int j = 0; j < uni.getDegree(i).getN(); j++)
        {
            sum++;
            temp = uni.getDegree(i).getStudent(j);
            cout << setw(14) << temp.getDNI() << setw(30) << temp.getName() << setw(10) << bool_to_string(temp.getGraduated()) << endl;
        }
    }
    cout << right;
    cout << endl
         << "Total number of students: " << sum << endl
         << endl;
}

void Menu::import()
{
    string dni, name, tempGraduated;
    bool graduated;
    string line;
    int noOfDegrees, noOfStudents;
    ifstream database("data.txt");

    if (!database.is_open())
    {
        cout << "File failed to open" << endl;
    }
    else
    {
        getline(database, line);
        if(line.size()<1) {database.close(); return;}
        noOfDegrees = stoi(line);

        for (int i = 0; i < noOfDegrees; i++)
        {
            getline(database, line);
            uni += Degree(line);
            getline(database, line);
            noOfStudents = stoi(line);
            for (int j = 0; j < noOfStudents; j++)
            {
                getline(database, line);
                stringstream ss(line);
                getline(ss, dni, ',');
                getline(ss, name, ',');
                getline(ss, tempGraduated, ',');
                graduated = to_bool(tempGraduated);
                uni.getDegree(i) += Student(dni, name, graduated);
            }
        }
        database.close();
    }
}

void Menu::start()
{
    string choice;
    bool correct;
    import();
    while (true)
    {
        correct = false;
        cout << endl
             << endl
             << "Welcome!" << endl
             << "1. Add or modify student." << endl
             << "2. Eliminate graduates." << endl
             << "3. List of students." << endl
             << "4. Exit." << endl;
        cout << "Your choice: ";
        while (!correct)
        {
            getline(cin, choice);
            if (choice.size() == 1 && choice[0] >= 49 && choice[0] <= 52)
                correct = true;
            else
                cout << "Please enter a digit from 1 to 4." << endl;
        }
        switch (stoi(choice))
        {
        case 1:
        {
            add();
            break;
        }
        case 2:
        {
            eliminate();
            break;
        }
        case 3:
        {
            list();
            break;
        }
        case 4:
        {
            save();
            return;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return;
}

void Menu::save()
{
    ofstream database("data.txt");
    Student temp;
    if (!database.is_open())
    {
        database << "File failed to open" << endl;
    }
    else
    {
        database << uni.getN();
        for (int i = 0; i < uni.getN(); i++)
        {
            database << endl
                     << uni.getDegree(i).getName()
                     << endl
                     << uni.getDegree(i).getN();
            for (int j = 0; j < uni.getDegree(i).getN(); j++)
            {
                temp = uni.getDegree(i).getStudent(j);
                database << endl
                         << temp.getDNI() << "," << temp.getName() << "," << temp.getGraduated();
            }
        }
        database.close();
    }
}

#endif