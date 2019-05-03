#include "Student.h"

using namespace std;

Student::Student()
{

}

Student::Student(int i, string n, string l, double g, string m, int a) // constructor that takes in student info as parameters 
{
    id = i;
    name = n;
    level = l;
    gpa = g;
    major = m;
    advisorID = a;
}

Student::~Student()
{

}

void Student::setAdvisorID(int aid)
{
    advisorID = aid;
}

int Student::getAdvisorID()
{
    return advisorID;
}

void Student::printStudent()
{
    cout << "Student ID: " << id << endl; 
    cout << "Name: " << name <<  endl; 
    cout << "Grade: " << level << endl; 
    cout << "GPA: " << gpa << endl;
    cout << "Major: " << major << endl; 
    cout << "Advisor ID: " << endl;

    if (advisorID == -1)
    {
        cout << "ERROR: No Advisor Found." << endl;
    }

    else
    {
        cout << advisorID << endl;
    }
}

double Student::getGPA()
{
    return gpa;
}

string Student::getMajor()
{
    return major;
}