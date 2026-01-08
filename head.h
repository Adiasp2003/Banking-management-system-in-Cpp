#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class InvalidLoginException
{
public:
    string message;

    InvalidLoginException() // constructor
    {
        message = "\nInvalid username or password\n"; // to display error message using message
    }
};

class User
{
protected:
    string username;
    string password;
    string role;
    int balance;

public:
    User()
    {
    }
    void set_username(string u)
    {
        username = u;
    }
    void set_password(string p)
    {
        password = p;
    }
    void set_role(string r)
    {
        role = r;
    }

    string getrole()
    {
        return role;
    }

    string getusername()
    {
        return username;
    }

    int get_balance()
    {
        return balance;
    }
};

class Authentication
{
public:
    User login()
    {
        string role, password, username;

        cout << "\nEnter the username: ";
        cin >> username;
        cout << "Enter the Password: ";
        cin >> password;

        // ifstream to open the file
        ifstream file("users.dat"); // users.data is the file name to store values

        if (!file.is_open())
        {
            cout << "\nError opening the user.dat file!\n"
                 << endl;
            exit(1);
        }

        // to check from information stored in the file and compared what user enteres
        string file_uname, file_pass, file_role, id, balance;
        bool found = false; // true or false

        while (file >> id >> file_uname >> file_pass >> file_role >> balance)
        {
            if (username == file_uname && password == file_pass)
            {
                found = true;
                break;
            }
        }

        file.close();

        if (found == false) // when any details of user not found
        {
            throw InvalidLoginException(); // to print error message
        }

        User user;
        user.set_username(file_uname);
        user.set_password(file_pass);
        user.set_role(file_role);

        cout << "\nLogin Successful!" << endl;
        cout << "Role: " << user.getrole() << endl;
        return user;
    }
};

void bankermenu();
void create_customer();
void view_all_customer();
void delete_customer();
void update_customer_password();

void customermenu(string loggedInuser);
int deposit(string loggedInuser);
int withdraw(string loggedInuser);
void transfer(string loggedInuser);
void viewBalance(string);
