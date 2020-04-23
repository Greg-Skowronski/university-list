#ifndef CHECK_H
#define CHECK_H
using namespace std;
#include <iostream>
#include <string>

bool to_bool(string s)
{
    return (s != "0" || s != "no") && (s == "1" || s == "yes");
}

string bool_to_string(bool b)
{
    if (b)
        return "yes";
    return "no";
}

bool dni_check(string dni)
{
    int length = dni.size();
    if (length == 9)
    {
        if (dni[8] >= 65 && dni[8] <= 90)
        {
            for (int i = 0; i < length - 1; i++)
            {
                if (dni[i] < 48 || dni[i] > 57)
                {
                    cout << "Incorrect DNI." << endl
                         << "Enter DNI of the student: ";
                    return false;
                }
            }
            return true;
        }
    }
    cout << "Incorrect DNI." << endl
         << "Enter DNI of the student: ";
    return false;
}

bool name_check(string name)
{
    int length = name.size();
    for (int i = 0; i < length; i++)
    {
        if ((name[i] < 65 || name[i] > 90) && (name[i] < 97 || name[i] > 122))
        {
            if (name[i] != 32 || name[0] == 32)
            {
                cout << "Incorrect input." << endl
                     << "Enter name of the student: ";
                return false;
            }
        }
    }
    if (length > 1)
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (name[i] == 32 && name[i + 1] == 32)
            {
                cout << "Incorrect input." << endl
                     << "Enter name of the student: ";
                return false;
            }
        }
    }
    return true;
}

bool graduated_check(string graduated)
{
    if (graduated.compare("yes") == 0 || graduated.compare("no") == 0)
        return true;
    cout << "Enter yes or no." << endl
         << "Has the student graduated? ";
    return false;
}

bool degree_check(string name)
{
    int length = name.size();
    for (int i = 0; i < length; i++)
    {
        if ((name[i] < 65 || name[i] > 90) && (name[i] < 97 || name[i] > 122) && (name[i]<49 || name[i]>57))
        {
            if (name[i] != 32 || name[0] == 32)
            {
                cout << "Incorrect input." << endl
                     << "Enter name of the degree: ";
                return false;
            }
        }
    }
    if (length > 1)
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (name[i] == 32 && name[i + 1] == 32)
            {
                cout << "Incorrect input." << endl
                     << "Enter name of the degree: ";
                return false;
            }
        }
    }
    return true;
}

#endif