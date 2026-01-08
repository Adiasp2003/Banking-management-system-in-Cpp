#include"head.h"

void customermenu(string loggedInuser)
{
    int choice;
    int balance;

    do
    {
        cout << "\n----Customer Dashboard ----\n";
        cout << "1.Deposit\n";
        cout << "2.Withdraw\n";
        cout << "3.Transfer\n";
        cout << "4.View Balance\n";
        cout << "5.Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the amount to be deposited: ";
            balance = deposit(loggedInuser);
            break;
        case 2:
            cout << "Enter the amount to be withdraw: ";
            balance = withdraw(loggedInuser);
            cout << "Deposite successful! New Balance: " << balance << endl;
            break;
        case 3:

            transfer(loggedInuser);
            break;
        case 4:
            viewBalance(loggedInuser);
            break;

        case 5:
            cout << "Exiting\n";
            exit(1);
            break;
        default:
            printf("Enter the valid choice\n");
        }
    } while (1);
}

int deposit(string loggedInuser)
{
    int amount;

    cin >> amount;

    ifstream inFile("users.dat");
    ofstream tempFile("temp.dat");
    string f_id, f_uname, f_pass, f_role;
    int balance;
    int updated_balance;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {
        if (f_uname == loggedInuser && f_role == "customer")
        {
            balance = balance + amount;
            updated_balance = balance;
        }
        tempFile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << balance << endl;
    }

    inFile.close();
    tempFile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");

    cout << "Deposite successful! New Balance: " << updated_balance << endl;
    return updated_balance;
}

int withdraw(string loggedInuser)
{
    int amount;
    cin >> amount;
    int updated_balance;

    ifstream inFile("users.dat");
    ofstream tempFile("temp.dat");
    string f_id, f_uname, f_pass, f_role;
    int balance;
    int found = 0;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {

        if (f_uname == loggedInuser && f_role == "customer")
        {
            if (amount > balance)
            {
                found = 1;
            }

            if (found == 0)
            {
                balance = balance - amount;
            }
            updated_balance = balance;
        }
        tempFile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << balance << endl;
    }

    inFile.close();
    tempFile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");

    if (found == 1)
    {
        cout << " Insufficient balance in your account\n";
    }
    return updated_balance;
}

void viewBalance(string loggedInuser)
{
    ifstream inFile("users.dat");
    string f_id, f_uname, f_pass, f_role;
    int balance;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {
        if (f_uname == loggedInuser && f_role == "customer")
        {
            break;
        }
    }

    inFile.close();

    cout << "Deposite successful! New Balance: " << balance << endl;
}

void transfer(string loggedInuser)
{

    string t_uname;
    cout << " Enter the transfer name\n";
    cin >> t_uname;

    ifstream inFile("users.dat");
    string f_id, f_uname, f_pass, f_role;
    int balance;
    int flag = 0;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {
        if (f_uname == t_uname && f_role == "customer")
        {
            flag = 1;
        }
    }
    if (flag == 0)
    {
        cout << "User not found\n";
    }

    inFile.close();

    int t_amount, found = 0;
    cout << "enter the amount to be transfered\n";
    cin >> t_amount;

    ifstream inFILE("users.dat");
    ofstream tempFile("temp.dat");

    // to withdraw from user
    while (inFILE >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {
        if (f_uname == loggedInuser && f_role == "customer")
        {
            if (t_amount > balance)
            {
                found = 1;
                cout <<"Insufficient balance\n";
            }

            if (found == 0)
            {
                balance = balance - t_amount;
            }
        }
        tempFile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << balance << endl;
    }

    inFILE.close();
    tempFile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");

    if (found == 1)
    {
        return;
    }

    ifstream infILE("users.dat");
    ofstream tempfile("temp.dat");

    // to transfer to other account
    while (infILE >> f_id >> f_uname >> f_pass >> f_role >> balance)
    {

        if (f_uname == t_uname && f_role == "customer")
        {
            balance = balance + t_amount;
        }
        tempfile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << balance << endl;
    }

    infILE.close();
    tempfile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");
}