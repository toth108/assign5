// MADALYN TOTH

#include <iostream>
#include <array>
#include "DLL.h"
#include "Person.h"

using namespace std;

class Faculty : public Person
{
    public:
        string dept;
        unsigned int numAdv;
        unsigned int maxArr;
        int *advIDArr;

        Faculty();
        Faculty(int i, string n, string l, string d);
        ~Faculty();

        void printFaculty();
        void printAdv();

        void addAdv(int aid);
        bool removeAdv(int advID);

        int getMaxArr();

        string getDept();
        int getNumAdv();
};