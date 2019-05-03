// MADALYN TOTH 

#include "Configure.h"

using namespace std;

int main (int argc, char** argv)
{
    Configure config;
    Menu menu;

    config.readFromFile();
    menu.displayMenu();
    config.run();

    return 0;
}