// MADALYN TOTH

#include "Faculty.h"

using namespace std;

Faculty::Faculty()
{
    
}

Faculty::Faculty(int i, string n, string l, string d) // constructor that takes in faculty info as parameters 
{
    id = i;
    name = n;
    level = l;
    dept = d;
    advIDArr = new int[4];
    numAdv = 0;
    maxArr = 4;

    for (int i = 0; i < 4; i++)
    {
        advIDArr[i] = -1;
    }
}

Faculty::~Faculty()
{
    delete [] advIDArr;
};

void Faculty::printFaculty() // prints out faculty info in terminal line by line 
{
    cout << "Faculty ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl; 
    cout << "Dept: " << dept << endl; 
    cout << "Advisee IDs: " << endl;
    printAdv();
    cout << endl;
}

void Faculty::printAdv() // prints a list of advisees of a faculty member 
{
    if (numAdv == 0)
    {
        cout << "ERROR: No Advisees Found." << endl;
    }

    else 
    {
        for (int i = 0; i < maxArr; i++)
        {
            if (advIDArr[i] != -1)
            {
                cout << advIDArr[i];

                if (i < numAdv - 1)
                {
                    cout << ", ";
                }
            }
        }
    }

    cout << endl;
}

void Faculty::addAdv(int aid) // add avdisee to faculty member 
{
    if (numAdv == maxArr) // if full, fix size 
    {
		int *temp1 = new int[numAdv];

		for (int i = 0; i < numAdv; i++) 
		{
			temp1[i] = advIDArr[i];
		}

		advIDArr = new int[numAdv * 2];

        maxArr = numAdv * 2;

		for (int i = 0; i < numAdv; i++)
		{
			advIDArr[i] = temp1[i];
		}

        for (int i = numAdv; i < numAdv * 2; i++)
        {
            advIDArr[i] = -1;
        }

        advIDArr[numAdv++] = aid;
	}

    else // if arr not full, add advisee 
    {
        int f = 0;

        for (int i = 0; i < maxArr; i++) // check if student already has this advisor 
        {
            if (advIDArr[i] == aid)
            {
                f = maxArr;
            }
        }

        while (f < maxArr) // if not, add advisor 
        {
            if (advIDArr[f] == -1)
            {
                advIDArr[f] = aid;

                numAdv++;

                break;
            }

            f++;
        }
    }
}

bool Faculty::removeAdv(int advID) // remove advisee from faculty member 
{
    bool deleted = false;

    for (int i = 0; i < maxArr; i++) // read through advisee list and remove 
    {
        if (advIDArr[i] == advID) 
        {
            advIDArr[i] = -1; 

            numAdv--;

            deleted = true;
        }
    }

    if (!deleted)
    {
        cout << "ERROR: Advisee not found." << endl;
    }

    return deleted;
}

int Faculty::getMaxArr() 
{
    return maxArr; 
}

string Faculty::getDept() 
{
    return dept; 
}

int Faculty::getNumAdv() 
{
    return numAdv; 
}