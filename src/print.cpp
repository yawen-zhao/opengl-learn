#include "../include/print.h"

void printMessage(vector<string>& msg)
{
    for(auto c: msg)
    {
        cout << c << " ";
    }
}