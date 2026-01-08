#include "head.h"

void bankermenu()
{
    int choice;

    do
    {
        cout << "\n----Banker Dashboard ----\n";
        cout << "1.Create Customer\n";
        cout << "2.View All customers\n";
        cout << "3.Delete customer account\n";
        cout << "4.Update customer account password\n";
        cout << "5.Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            create_customer();
            break;
        case 2:
            view_all_customer();
            break;
        case 3:
            delete_customer();
            break;
        case 4:
        update_customer_password();
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

void create_customer()
{
    string id, username, password;
    int balance = 0;
    string role = "customer"; // default as banker is creating the customer id

    cout << "\nEnter customer ID: ";
    cin >> id;
    cout << "Enter the customer username: ";
    cin >> username;
    cout << "Enter the customer password: ";
    cin >> password;

    // check if username and id exists
    ifstream inFile("users.dat");
    string f_id, f_uname, f_pass, f_role;
    int f_balance;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> f_balance)
    {
        if (f_id == id)
        {
            cout << "ID already exists.\n";
            cout << "Try again with different ID\n";
            inFile.close();
            return;
        }
        if (f_uname == username)
        {
            cout << "USERNAME already exists.\n";
            cout << "Try again with different username\n";
            inFile.close();
            return;
        }
    }
    inFile.close();

    // to append into file
    ofstream outFile("users.dat", ios::app);
    outFile << id << " " << username << " " << password << " " << role << " " << balance;

    outFile.close();

    cout << "\nCustomer Account created SUCCESSFULLY\n";
}
void view_all_customer()
{
    ifstream inFile("users.dat");
    string f_id, f_uname, f_pass, f_role;
    int f_balance;
    cout << "\n***All Customer account Details***\n";
    cout << "\nID      USERNAME\n";
    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> f_balance)
    {
        if (f_role == "customer")
        {
            cout << f_id;
            cout << "\t" << f_uname << endl;
        }
    }
    inFile.close();
    cout << "\nEnd of all customer details\n";
}

void delete_customer()
{
    string id, username;
    int balance = 0;
    string role = "customer"; // default as banker is creating the customer id

    cout << "\nEnter customer ID: ";
    cin >> id;
    cout << "Enter the customer username: ";
    cin >> username;

    // check if username and id exists
    ifstream inFile("users.dat");
    ofstream tempFile("temp.dat");
    string f_id, f_uname, f_pass, f_role;
    int f_balance;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> f_balance)
    {
        if (f_id == id || f_uname == username)
        {
            continue;
        }
        tempFile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << f_balance << endl;
    }
    inFile.close();
    tempFile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");

    cout << "\nCustomer Account deleted SUCCESSFULLY\n";
}

void update_customer_password()
{
    string id, username, password;
    int balance = 0;
    string role = "customer"; // default as banker is creating the customer id

    cout << "\nEnter customer ID: ";
    cin >> id;
    cout << "Enter the customer username: ";
    cin >> username;
    cout << "Enter the new customer password: ";
    cin >> password;

    // check if username and id exists
    ifstream inFile("users.dat");
    ofstream tempFile("temp.dat");
    string f_id, f_uname, f_pass, f_role;
    int f_balance;

    while (inFile >> f_id >> f_uname >> f_pass >> f_role >> f_balance)
    {
        if (f_id == id || f_uname == username)
        {
            f_pass = password;
        }
        tempFile << f_id << " " << f_uname << " " << f_pass << " " << f_role << " " << f_balance << endl;
    }
    inFile.close();
    tempFile.close();

    remove("users.dat");
    rename("temp.dat", "users.dat");

    cout << "\nCustomer Account deleted SUCCESSFULLY\n";
}