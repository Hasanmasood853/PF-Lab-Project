#include <iostream>
#include <string>
using namespace std;
bool adminPanelLogin();
string adminPass = "1234";
string adminUser = "admin";

const int maxFlights = 8;

int main()
{
    int choice;
    do
    {
        cout << "*************************************\n";
        cout << "     Airline Management System       \n";
        cout << "*************************************\n";
        cout << "Are you admin or passenger?\n1.Admin Panel    2.Passenger Panel   3.Exit\nEnter your choice (1 2 or 3): ";
        cin >> choice;
        while (choice < 1 && choice > 3)
        {
            cout << "Invalid choice! Enter again: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
        {
            if (adminPanelLogin())
            {
                int adminChoice;
                cout << "\n===== Admin Panel =====\n";
                cout << "1.Change Password\n2.Current Registered Flights & Passengers\n3.Add/Remove Passenger\n4.Update Passenger Data\n5.Add/Remove Flights\n6.Check reports\nEnter your choice: ";
                cin >> adminChoice;
                while (adminChoice < 1 || adminChoice > 6)
                {
                    cout << "Invalid choice! Enter again (1-6): ";
                    cin >> adminChoice;
                }
                switch (adminChoice)
                {
                case 1:
                {
                    string newPass, confirmPass;

                    cout << "Enter New Password: ";
                    cin.ignore();
                    getline(cin, newPass);

                    cout << "Confirm New Password: ";
                    getline(cin, confirmPass);

                    while (newPass != confirmPass)
                    {
                        cout << "Passwords do not match! Try again:\n";
                        cout << "New Password: ";
                        getline(cin, newPass);
                        cout << "Confirm Password: ";
                        getline(cin, confirmPass);
                    }

                    adminPass = newPass;
                    break;
                }
                }
            }
            break;
        case 2:

            break;
        case 3:
            cout << "Exit Successful. Thanks\n";
        }
        }

    } while (choice != 3);
    return 0;
}
bool adminPanelLogin()
{
    string userName, userPass;
    cout << "\nEnter your username: ";
    cin.ignore();
    getline(cin, userName);
    cout << "Enter your password: ";
    ;
    getline(cin, userPass);
    while ((userName != adminUser) || (userPass != adminPass))
    {
        cout << "Invalid username or password. Please enter again: ";
        cout << "\nUsername: ";
        getline(cin, userName);
        cout << "Password: ";
        getline(cin, userPass);
    }
    return true;
}
