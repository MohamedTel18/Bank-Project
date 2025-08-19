#include <iostream>
#include "clsLogInScreen.h"

using namespace std;

int main()

{
    while (true)
    {
        if (!clsLogInScreen::ShowLogInScreen())
        {
            break;
        }
    }
    

    system("pause>0");
    return 0;
}