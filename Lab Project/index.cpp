#include <iostream>
#include <string>
using namespace std;
bool adminPanelLogin();
string adminPass = "1234";
string adminUser = "admin";
const int maxFlights = 8;
int flightCount = 4;
struct Flight
{
    int flightID;
    string flightNumber;
    string destination;
    string fromLocation;
    string departureTime;
    string arrivalTime;
    int totalSeats;
    int reservedSeats;
    int flightFare;
    string flightNames[maxFlights] = {"Emirates", "Airblue", "Saudi Airline", "PIA"};
    string status;
};

Flight flights[maxFlights];
void addFlight();
void removeFlight();

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
                case 5:
                {
                    int addRemChoice;
                    cout << "Choose an option:\n1.Add Flights\t2.Remove Flights\n";
                    cin >> addRemChoice;
                    while (choice != 1 && choice != 2)
                    {
                        cout << "Invalid Choice! Enter again (1 or 2): ";
                        cin >> addRemChoice;
                    }
                    if (addRemChoice == 1)
                    {
                        addFlight();
                    }
                    else if (addRemChoice == 2)
                    {
                        removeFlight();
                    }
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
void addFlight()
{
    if (flightCount >= maxFlights)
    {
        cout << "Flight storage full\n";
        return;
    }

    cout << "\n===== ADD FLIGHT =====\n";
    cout << "Enter Flight ID (e.g 101): ";
    cin >> flights[flightCount].flightID;
    cin.ignore();

    cout << "Enter Flight Number (e.g EK-502): ";
    getline(cin, flights[flightCount].flightNumber);

    cout << "Enter From Location (e.g Karachi): ";
    getline(cin, flights[flightCount].fromLocation);

    cout << "Enter Destination (e.g Dubai): ";
    getline(cin, flights[flightCount].destination);

    cout << "Enter Departure Time (e.g 10:30 AM): ";
    getline(cin, flights[flightCount].departureTime);

    cout << "Enter Arrival Time (e.g 01:45 PM): ";
    getline(cin, flights[flightCount].arrivalTime);

    cout << "Enter Total Seats (e.g 180): ";
    cin >> flights[flightCount].totalSeats;

    cout << "Enter Reserved Seats (e.g 50): ";
    cin >> flights[flightCount].reservedSeats;

    cout << "Enter Flight Fare (e.g 25000): ";
    cin >> flights[flightCount].flightFare;
    cin.ignore();
    if (flights[flightCount].reservedSeats >= flights[flightCount].totalSeats)
    {
        flights[flightCount].status = "Full";
    }
    else
    {
        flights[flightCount].status = "Available";
    }

    flightCount++;
    cout << "\nFlight Added Successfully\n";
}
void removeFlight()
{
    
}
