#include "head.h"

int main()
{

    Authentication auth;
    User loggedInUser;

    try
    {
        loggedInUser = auth.login();
        if (loggedInUser.getrole() == "banker")
        {
            //cout << "\n------ Banker Dashboard-----\n";
            bankermenu();
            // bankerfun()
        }
        else if (loggedInUser.getrole() == "customer")
        {
            //cout << "\n------ Customer Dashboard-----\n";
            customermenu(loggedInUser.getusername());
        }

        else
        {
            cout << "\nInvalid role\n";
        }
    }

    catch (InvalidLoginException &e)
    {
        cout << e.message << endl;
    }
}
