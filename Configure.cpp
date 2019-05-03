// MADALYN TOTH 

#include <string>
#include <fstream>
#include "Configure.h"

using namespace std;

Configure::Configure()
{

}

Configure::~Configure()
{

}

void Configure::readFromFile()
{
    ifstream masterStudentFile;
    ifstream masterFacultyFile;

    // student file 

    int i = 0;
    string n = "";
    string l = "";
    double g = 0;
    string m = "";
    int a = -1;

    string line;
    int numStudents = 0;
    int lineCount = 1;

	masterStudentFile.open("studentTable.txt");

    if (masterStudentFile.is_open())
    {
        try
        {
       		getline(masterStudentFile, line); // get number of students 

            if (line != "")
            {
                numStudents = stoi(line);
            }
        }

        catch (exception e)
        {
            cout << "ERROR: Incorrect File Format" << endl;
        }

        for (int j = 0; j < (7 * numStudents); ++j) // new student every 7 lines 
        {
            getline(masterStudentFile, line);

            switch (lineCount)
            {
                case 1:
                {
                    if (line != "--")
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    break;
                }

                case 2:
                {
                    try
                    {
                   		i = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    break;
                }

                case 3:
                {
                    n = line;

                    break;
                }

                case 4:
                {
                    l = line;

                    break;
                }

                case 5:
                {
                    try
                    {
                   		g = stod(line);
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    break;
                }

                case 6:
                {
                    m = line;

                    break;
                }

                case 7: // new node from student and insert node to tree 
                {
                    try
                    {
                   		a = stoi(line);

                        Student *stud = new Student(i, n, l, g, m, a);

                        TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

                        masterStudent.insert(studNode);
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }
                    break;
                }

                default:break;
            }

            lineCount++;

            if (lineCount > 7)
            {
                lineCount = 1;
            }
        }
    }

    else
    {
        cout << "ERROR: Student database not found. Running with no current students." << endl; 
    }

    masterStudentFile.close();

    // faculty file 

    int numFaculty = 0;

    int fi = 0;
    string fn = "";
    string fl = "";
    string fd = "";
    int advID = 0;

    lineCount = 1;
    int createdCount = 0;

    int na = 0;

    masterFacultyFile.open("facultyTable.txt");

    if (masterFacultyFile.is_open())
    {
        try
        {
       		getline(masterFacultyFile, line); // number of faculty 

            if (line != "")
            {
                numFaculty = stoi(line);
            }
        }

        catch (exception e)
        {
            cout << "ERROR: Incorrect File Format" << endl;
        }

        while (getline(masterFacultyFile, line)) // read through file and create faculty 
        {
            switch (lineCount)
            {
                case 1:
                {
                    if (line != "--")
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    break;
                }

                case 2:
                {
                    try
                    {
                   		fi = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    break;
                }

                case 3:
                {
                    fn = line;

                    break;
                }

                case 4:
                {
                    fl = line;

                    break;
                }

                case 5:
                {
                    fd = line;

                    break;
                }

                case 6: // get number of advisees and set next block as Adv IDs
                {
                    try
                    {
                   		na = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: Incorrect File Format" << endl;
                    }

                    Faculty *fac = new Faculty(fi, fn, fl, fd);

                    createdCount++;

                    for (int k = 0; k < na; ++k)
                    {
                        getline(masterFacultyFile, line);

                        try
                        {
                       		advID = stoi(line);
                        }

                        catch (exception e)
                        {
                            cout << "ERROR: Incorrect File Format" << endl;
                        }

                        fac->addAdv(advID);
                    }

                    // new faculty node and insert to tree 
                    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, fi);

                    masterFaculty.insert(facNode);

                    break;
                }

                default:break;
            }

            ++lineCount;

            if (createdCount == numFaculty)
            {
                break;
            }

            if (lineCount > 6)
            {
                lineCount = 1;
            }
        }
    }

    else
    {
        cout << "ERROR: Faculty database not found. Running with no current faculty." << endl; 
    }

    masterFacultyFile.close();
}

void Configure::printMasterStudent(TreeNode<Student> *n) // prints master student tree from root
{
    if (n != NULL)
    {
        if (n->left != NULL)
        {
            printMasterStudent(n->left);
        }

        n->data->printStudent();

        if (n->right != NULL)
        {
            printMasterStudent(n->right);
        }
    }

    else
    {
        cout << "ERROR: Student tree is empty." << endl;
    }
}

void Configure::printMasterFaculty(TreeNode<Faculty> *n) // prints master faculty tree from root
{
    if (n != NULL)
    {
        if (n->left != NULL)
        {
            printMasterFaculty(n->left);
        }

        n->data->printFaculty();

        if (n->right != NULL)
        {
            printMasterFaculty(n->right);
        }
    }

    else
    {
        cout << "ERROR: Faculty tree is empty." << endl;
    }
}

void Configure::addStudent() // create new student 
{
    int i;
    string n;
    string l;
    double g;
    string m;
    int a;

    int answerInt = 0;
    double answerDbl = 0;
    string answer = "";

    while (true)
    {
        cout << "ID of student: " << endl;

        answerInt = 0;
        answer = "";
        cin >> answer;

        try
        {
            i = stoi(answer);

            if (i > 0) // if student ID is positive and does not already exist 
            {
                if (!masterStudent.isInTree(i))
                {
                    break;
                }

                else
                {
                    cout << "Student already exists. Try another." << endl;
                }
            }

            else
            {
                cout << "Invalid input. Try again." << endl;
            }
        }

        catch (exception e)
        {
            cout << "Invalid input. Try again." << endl;
        }
    }

    string line;

    cout << "Name of student: " << endl;
    cin.ignore();
    getline(cin, n);

    cout << "Grade: " << endl;
    getline(cin, l);

    while (true)
    {
        cout << "GPA: " << endl;

        answerDbl = 0;
        answer = "";
        cin >> answer;

        try
        {
            g = stod(answer);

            if (g > 0 && g < 5)
            {
                break;
            }

            else
            {
                cout << "ERROR: Enter a GPA between 0 and 5." << endl;
            }
        }

        catch (exception e)
        {
            cout << "ERROR: Invalid input. Try again." << endl;
        }
    }

    cout << "Major: " << endl;
    cin.ignore();
    getline(cin, m);

    if (!masterFaculty.isEmpty()) // prompt to check if student has advisor 
    {
        cout << "Does this student have an advisor? Enter '1' for Yes OR '2' for No: " << endl;

        while (true)
        {
            answerInt = 0;
            answer = "";
            cin >> answer;

            try
            {
                answerInt = stoi(answer);

                if (answerInt == 1 || answerInt == 2)
                {
                    break;
                }
            }

            catch (exception e)
            {
                cout << "ERROR: Invalid input. Try again." << endl;
            }
        }

        if (answerInt == 1) // if student has advisor, prompt for faculty ID
        {
            cout << "Advisor ID: " << endl;

            while (true)
            {
                answerInt = 0;
                answer = "";
                cin >> answer;

                try // check if input is int, then find in tree 
                {
                    a = stoi(answer);

                    if (masterFaculty.isInTree(a)) // if found, add student to faculty member and assign student's advisor 
                    {
                        Faculty *fac = masterFaculty.search(a);

                        fac->addAdv(i);

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Faculty member not found." << endl;
                    }
                }

                catch (exception e)
                {
                    cout << "Enter an integer." << endl;
                }
            }
        }

        else
        {
            a = -1;
        }
    }

    else
    {
        a = -1;
    }

    Student *stud = new Student(i, n, l, g, m, a);

    TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

    masterStudent.insert(studNode);
}

void Configure::addFaculty() // create new faculty member 
{
    int i;
    string n;
    string l;
    string d;

    int answerInt = 0;
    int numEntries = 0;
    string answer = "";

    while (true)
    {
        cout << "ID of faculty member: " << endl;

        answerInt = 0;
        answer = "";
        cin >> answer;

        try
        {
            i = stoi(answer);

            if (i > 0)
            {
                break;
            }
        }

        catch (exception e)
        {
            cout << "ERROR: Invalid input. Try again." << endl;
        }
    }

    string line;

    cout << "Name of faculty member: " << endl;
    cin.ignore();
    getline(cin, n);

    cout << "Level of faculty member: " << endl;
    getline(cin, l);

    cout << "Department of faculty member: " << endl;
    getline(cin, d);

    Faculty *fac = new Faculty(i, n, l, d);

    if (!masterStudent.isEmpty()) // if faculty has / can have advisees
    {
        cout << "Does this facuty member have advisees? Enter '1' for Yes OR '2' for No: " << endl;

        while (true)
        {
            answerInt = 0;
            answer = "";
            cin >> answer;

            try
            {
                answerInt = stoi(answer);

                if (answerInt == 1 || answerInt == 2)
                {
                    break;
                }
            }

            catch (exception e)
            {
                cout << "ERROR: Invalid input. Try again: ";
            }
        }

        if (answerInt == 1 && !masterStudent.isEmpty()) // if yes, prompt for number of advisees 
        {
            cout << "How many students does this faculty member advise?" << endl;

            while (true)
            {
                cout << "Enter an integer: " << endl;

                answerInt = 0;
                answer = "";
                cin >> answer;

                try // check if input is int 
                {
                    answerInt = stoi(answer);

                    if (answerInt > 0 && answerInt <= masterStudent.getSize())
                    {
                        numEntries = answerInt;
                        break;
                    }

                    else
                    {
                        cout << "Enter an integer less than or equal to " << masterStudent.getSize() << "." << endl;
                    }
                }

                catch (exception e)
                {
                    cout << "ERROR: Invalid input. Enter an integer." << endl;
                }
            }

            for (int v = 0; v < numEntries; v++)
            {
                while (true)
                {
                    cout << "Enter a Student ID (" << numEntries - v << " remaining): " << endl;

                    answerInt = 0;
                    answer = "";

                    cin >> answer;

                    try // check if input is int, then find in tree 
                    {
                        answerInt = stoi(answer);

                        if (masterStudent.isInTree(answerInt)) // if found, add student to faculty member and assign student's advisor 
                        {
                            fac->addAdv(answerInt);

                            masterStudent.search(answerInt)->setAdvisorID(i);

                            break;
                        }

                        else
                        {
                            cout << "ERROR: Student not found." << endl;
                        }
                    }

                    catch (exception e)
                    {
                        cout << "Enter an integer." << endl;
                    }
                }
            }
        }
    }

    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, i);

    masterFaculty.insert(facNode);
}

// creates new student with parameters
void Configure::addStudentFromFile(int i, string n, string l, double g, string m, int a) 
{
    Student *stud = new Student(i, n, l, g, m, a);

    TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

    masterStudent.insert(studNode);
}

// creates new faculty member with parameters
void Configure::addFacultyFromFile(int i, string n, string l, string d)
{
    Faculty *fac = new Faculty(i, n, l, d);

    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, i);

    masterFaculty.insert(facNode);
}

// prints student 
void Configure::displayStudentInfo(int i)
{
    if (masterStudent.isInTree(i))
    {
        masterStudent.search(i)->printStudent();
    }

    else
    {
        cout << "ERROR: Student does not exist not in system." << endl;
    }
}

// prints faculty 
void Configure::displayFacultyInfo(int i)
{
    if (masterFaculty.isInTree(i))
    {
        masterFaculty.search(i)->printFaculty();
    }

    else
    {
        cout << "ERROR: Faculty member does not exist not in system." << endl;
    }
}

TreeNode<Student>* Configure::getMasterStudentRoot()
{
    return masterStudent.getRoot();
}

TreeNode<Faculty>* Configure::getMasterFacultyRoot()
{
    return masterFaculty.getRoot();
}

// check if input is viable 
int Configure::checkInput(int l, int u, string m)
{
    string answer;
    int answerInt;

    while (true)
    {
        cout << "\n" << m;

        answerInt = 0;
        answer = "";
        cin >> answer;

        try // check if input is int 
        {
            answerInt = stoi(answer);

            if (answerInt < u && answerInt > l)
            {

                return answerInt;
            }

            else
            {
                cout << "ERROR: Please try again." << endl;
            }
        }

        catch (exception e)
        {
            cout << "ERROR: Invalid input. Enter an integer." << endl;
        }
    }
}

// runs based on menu number entered 
void Configure::run()
{
    bool running = true;

    while (running)
    {
        int response;

        response = checkInput(-1, 14, "Select an option from the menu: ");

        switch (response)
        {
            case 1: // print all students 
            {
                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                cout << endl;
                printMasterStudent(masterStudent.getRoot());

                break;
            }

            case 2: // print all faculty 
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No faculty members found in database." << endl;

                    break;
                }

                cout << endl;
                printMasterFaculty(masterFaculty.getRoot());

                break;
            }

            case 3: // find student info 
            {
                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                int t;

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        displayStudentInfo(t);

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Student does not exist in database. Enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            case 4: // find faculty info 
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No faculty members found in database." << endl;

                    break;
                }

                int t;

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        displayFacultyInfo(t);

                        break;
                    }
                }

                break;
            }

            case 5: // print student advisor 
            {
                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                int t;

                cout << "Current students in database: " << endl;

                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        displayFacultyInfo(masterStudent.search(t)->getAdvisorID());

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Student does not exist in database. Enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            case 6: // print all advisees of faculty member 
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No faculty members found in database." << endl;

                    break;
                }

                int t;

                cout << "Current faculty members in database: " << endl;
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        Faculty *fac = masterFaculty.search(t);

                        for (int i = 0; i < fac->getMaxArr(); ++i)
                        {
                            if (fac->advIDArr[i] != -1)
                            {
                                displayStudentInfo(fac->advIDArr[i]);
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Faculty member does not exist in database. Enter a valid ID." << endl;
                    }
                }

                break;
            }

            case 7: // add new student 
            {
                addStudent();

                cout << "Student Added" << endl;
                cout << "Returning to Menu. Enter '0' to view menu options." << endl;              

                break;
            }

            case 8: // delete student 
            {
                int t;

                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                cout << "Current students in database: " << endl;
                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        if (masterStudent.search(t)->getAdvisorID() != -1)
                        {
                            masterFaculty.search(masterStudent.search(t)->getAdvisorID())->removeAdv(t);
                        }

                        masterStudent.deleteNode(t);

                        cout << "Student Deleted" << endl;
                        cout << "Returning to Menu. Enter '0' to view menu options." << endl;

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Student does not exist in database. Enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            case 9: // add faculty member 
            {
                addFaculty();

                cout << "Faculty Added" << endl;
                cout << "Returning to Menu. Enter '0' to view menu options." << endl;

                break;
            }

            case 10: // delete faculty member 
            {
                int t;

                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                cout << "Current faculty members in database: ";
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        if (masterFaculty.search(t)->numAdv > 0)
                        {
                            for (int i = 0; i < masterFaculty.search(t)->maxArr; ++i)
                            {
                                if (masterFaculty.search(t)->advIDArr[i] != -1)
                                {
                                    masterStudent.search(masterFaculty.search(t)->advIDArr[i])->setAdvisorID(-1);
                                }
                            }
                        }
                        masterFaculty.deleteNode(t);

                        cout << "Faculty Deleted" << endl;
                        cout << "Returning to Menu. Enter '0' to view menu options." << endl;

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Faculty member does not exist in database. Enter a valid Faculty ID." << endl;
                    }
                }

                break;
            }

            case 11: // change student advisor 
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No faculty members found in database." << endl;

                    break;
                }

                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                int f;
                int s;

                cout << "Current students in database: ";
                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    s = checkInput(0, 10000, "Enter a Student ID: ");

                    if (masterStudent.isInTree(s))
                    {
                        while (true)
                        {
                            f = checkInput(0, 10000, "Enter a Faculty ID: ");

                            if (masterFaculty.isInTree(f))
                            {
                                break;
                            }

                            else
                            {
                                cout << "ERROR: Faculty member does not exist in database. Enter a valid Faculty ID." << endl;
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Student does not exist in database. Enter a valid Student ID." << endl;
                    }
                }

                masterStudent.search(s)->setAdvisorID(f);

                masterFaculty.search(f)->addAdv(s);

                cout << "Advisor has been changed." << endl;
                cout << "Returning to Menu. Enter '0' to view menu options." << endl;

                break;
            }

            case 12: // remove advisee 
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "ERROR: No faculty members found in database." << endl;

                    break;
                }

                if (masterStudent.isEmpty())
                {
                    cout << "ERROR: No students found in database." << endl;

                    break;
                }

                int f;
                int s;

                cout << "Current faculty members in database: " << endl;
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    f = checkInput(0, 10000, "Enter Faculty ID: ");

                    if (masterFaculty.isInTree(f))
                    {
                        cout << "Faculty Member currently avises: ";
                        masterFaculty.search(f)->printAdv();

                        while (true)
                        {
                            s = checkInput(0, 10000, "Enter Student ID: ");

                            if (masterStudent.isInTree(s))
                            {
                                break;
                            }

                            else
                            {
                                cout << "ERROR: Student does not exist in database. Enter a valid Student ID." << endl;
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "ERROR: Faculty member does not exist in database. Enter a valid Faculty ID." << endl;
                    }
                }

                if (masterFaculty.search(f)->removeAdv(s))
                {
                    masterStudent.search(s)->setAdvisorID(-1);

                    cout << "Advisor has been removed." << endl; 
                    cout << "Returning to Menu. Enter '0' to view menu options." << endl;
                }

                else
                {
                    cout << "ERROR: Advisor could not be removed." << endl;
                    cout << "Returning to Menu. Enter '0' to view menu options." << endl;
                }

                break;
            }

            case 13: // exit program 
            {
                running = false;
                break;
            }

            default: // '0' to view menu 
            {
                Menu m;

                m.displayMenu();

                break;
            }
        }
    }
}