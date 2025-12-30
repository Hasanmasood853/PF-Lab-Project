#include <iostream>
#include <string>
using namespace std;
// Login system
bool loginPanel(string initialUser, string initialPass);
string adminPass = "1234";
string adminUser = "admin";
string passengerUser = "user";
string passengerPass = "1234";

// flights
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
    string flightName;
    string status;
};

Flight flights[maxFlights];
void addFlight();
void removeFlight();
void viewFlights();
void initializeFlights();

// Passengers
struct Passenger
{
    int flightID;
    int seats[5];
};
void bookFlight();
int main()
{
    initializeFlights();
    int choice;

    do
    {
        cout << "\n*************************************\n";
        cout << "     Airline Management System       \n";
        cout << "*************************************\n";
        cout << "Are you admin or passenger?\n1.Admin Panel    2.Passenger Panel   3.Exit\n";
        cout << "Enter your choice (1 2 or 3): ";
        cin >> choice;

        while (choice < 1 || choice > 3)
        {
            cout << "Invalid choice! Enter again: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "\nHello Admin! Enter your valid credentials to Login";
            if (loginPanel(adminUser, adminPass))
            {
                bool adminActive = true;
                while (adminActive)
                {

                    int adminChoice;
                    cout << "\n===== Admin Panel =====\n";
                    cout << "1.Change Password\n2.Current Registered Flights & Passengers\n3.Add/Remove Passenger\n4.Update Passenger Data\n5.Add/Remove Flights\n6.Check reports\n7.Exit\nEnter your choice: ";
                    cin >> adminChoice;

                    while (adminChoice < 1 || adminChoice > 7)
                    {
                        cout << "Invalid choice! Enter again (1-7): ";
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
                        while ((newPass != confirmPass) || newPass == adminPass)
                        {
                            if (newPass == adminPass)
                            {
                                cout << "Error: New password cannot be the same as the old password!\n";
                            }
                            else
                            {
                                cout << "Passwords do not match! Try again:\n";
                            }
                            cout << "New Password: ";
                            getline(cin, newPass);
                            cout << "Confirm Password: ";
                            getline(cin, confirmPass);
                        }
                        adminPass = newPass;
                        cout << "Password Changed Successfully.\n";
                        break;
                    }
                    case 2:
                        viewFlights(); // add view passengers also
                        break;
                    case 3:
                        // add and remove passengers
                        break;
                    case 4:
                        // Update passenger data
                        break;
                    case 5:
                    {
                        int addRemChoice;
                        cout << "Choose an option:\n1.Add Flights\t2.Remove Flights\n";
                        cin >> addRemChoice;
                        while (addRemChoice != 1 && addRemChoice != 2)
                        {
                            cout << "Invalid Choice! Enter again (1 or 2): ";
                            cin >> addRemChoice;
                        }
                        if (addRemChoice == 1)
                            addFlight();
                        else
                            removeFlight();
                        break;
                    }
                    case 6:
                        // check report related to flight and passenger
                        break;
                    case 7:
                        adminActive = false;
                        cout << "Logged out successfully.\n";
                        break;
                    }
                }
            }
            break;
        }
        case 2:
        {
            cout << "\nHello Passenger! Enter your valid credentials to Login\n";
            if (loginPanel(passengerUser, passengerPass))
            {
                bool passengerActive = true;
                while (passengerActive)
                {
                    int passengerChoice;
                    viewFlights();

                    cout << "\n===== Welcome to Passenger Panel =====\n";
                    cout << "1.Book Flight\n2.Cancel Reservations\n3.View Available flights\n4.Generate Booking Reports\n5.Logout\n";
                    cout << "Choose an option: ";
                    cin >> passengerChoice;

                    while (passengerChoice < 1 || passengerChoice > 5)
                    {
                        cout << "Invalid Choice! Enter again (1-5): ";
                        cin >> passengerChoice;
                    }

                    switch (passengerChoice)
                    {
                    case 1:
                        bookFlight();
                        break;
                    case 2:
                        cout << "Cancel feature coming soon.\n";
                        break;
                    case 3:
                        viewFlights();
                        break;
                    case 4:
                        cout << "Report feature coming soon.\n";
                        break;
                    case 5:
                        passengerActive = false;
                        cout << "Logged out successfully.\n";
                        break;
                    }
                }
            }
            break;
        }
        case 3:
            cout << "Exiting System. Thank you!\n";
            break;
        }

    } while (choice != 3);

    return 0;
}
void bookFlight()
{
    // flight selection
    int givenFlightID, foundIdx = -1;
    cout << "\nGive details to select flight for booking\n";
    cout << "Enter flight id to select: ";
    cin >> givenFlightID;
    while (foundIdx == -1)
    {
        for (int i = 0; i < flightCount; i++)
        {
            if (flights[i].flightID == givenFlightID)
            {
                foundIdx = i;
                break;
            }
        }
        if (foundIdx == -1)
        {
            cout << "No Flight found for this id! Enter ID Again: ";
            cin >> givenFlightID;
        }
    }
    cout << "Flight Found for this ID: " << givenFlightID << endl;
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "ID    Number    From      To      Fare   Status      Flight Name\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << flights[foundIdx].flightID << "   "
         << flights[foundIdx].flightNumber << "    "
         << flights[foundIdx].fromLocation << "    "
         << flights[foundIdx].destination << "       "
         << flights[foundIdx].flightFare << "    "
         << flights[foundIdx].status;
    if (flights[foundIdx].status == "Full")
    {
        cout << "          ";
    }
    else
    {
        cout << "     ";
    }
    cout << flights[foundIdx].flightName << endl;

    // seats booking
    if (flights[foundIdx].status == "Available" && flights[foundIdx].reservedSeats < flights[foundIdx].totalSeats)
    {
        int seatsNum, remainingSeats;
        remainingSeats = flights[foundIdx].totalSeats - flights[foundIdx].reservedSeats;
        cout << "\nEnter number of seats you want to book (Min=1,Max=5): ";
        cin >> seatsNum;
        while (seatsNum < 1 || seatsNum > 5 || remainingSeats < seatsNum)
        {
            if (remainingSeats < seatsNum)
            {
                cout << "Seats are not available! Only " << remainingSeats << " seats left\nEnter no of seats again: ";
            }
            else
            {
                cout << "Invalid no of seats! You can book Min=1 and Max=5 seat Enter again: ";
            }
            cin >> seatsNum;
        }
        cout << "Booking confirmed!\n";
        flights[foundIdx].reservedSeats += seatsNum;

        if (flights[foundIdx].reservedSeats >= flights[foundIdx].totalSeats)
        {
            flights[foundIdx].status = "Full";
        }
    }
    else
    {
        cout << "Sorry, this flight is fully booked.\n";
    }
}

bool loginPanel(string initialUser, string initialPass)
{
    string userName, userPass;
    cout << "\nEnter your username: ";
    cin.ignore();
    getline(cin, userName);
    cout << "Enter your password: ";
    ;
    getline(cin, userPass);
    while ((userName != initialUser) || (userPass != initialPass))
    {
        cout << "Invalid username or password. Please enter again: ";
        cout << "\nUsername: ";
        getline(cin, userName);
        cout << "Password: ";
        getline(cin, userPass);
    }
    return true;
}

void initializeFlights()
{
    flights[0] = {101, "EK-502", "KHI", "DXB", "10:30 AM", "01:45 PM", 180, 50, 25000, "Emirates", "Available"};
    flights[1] = {102, "AB-112", "ISB", "LHE", "08:00 AM", "09:00 AM", 150, 150, 12000, "Airblue", "Full"};
    flights[2] = {103, "SA-990", "PEW", "RUH", "11:00 PM", "04:30 AM", 200, 120, 45000, "Saudi Airline", "Available"};
    flights[3] = {104, "PK-301", "LHR", "KHI", "02:00 PM", "11:30 PM", 250, 200, 85000, "PIA", "Available"};
    flightCount = 4;
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
    cout << "Enter Flight Name (e.g Airblue): ";
    getline(cin, flights[flightCount].flightName);
    cout << "Enter Flight Number (e.g EK-502): ";
    getline(cin, flights[flightCount].flightNumber);

    cout << "Enter From Location Code (e.g KHI): ";
    getline(cin, flights[flightCount].fromLocation);

    cout << "Enter Destination Code (e.g DXB): ";
    getline(cin, flights[flightCount].destination);

    cout << "Enter Departure Time (e.g 10:30 AM): ";
    getline(cin, flights[flightCount].departureTime);

    cout << "Enter Arrival Time (e.g 01:45 PM): ";
    getline(cin, flights[flightCount].arrivalTime);

    cout << "Enter Total Seats (e.g 180): ";
    cin >> flights[flightCount].totalSeats;

    cout << "Enter Flight Fare (e.g 25000): ";
    cin >> flights[flightCount].flightFare;
    cin.ignore();
    flights[flightCount].reservedSeats = 0;
    flights[flightCount].status = "Available";
    flightCount++;
    cout << "\nFlight Added Successfully\n";
}
void removeFlight()
{
    int delFlightID;
    cout << "\n===== DELETE FLIGHT =====\n";
    cout << "Enter ID to delete flight (e.g 101): ";
    cin >> delFlightID;
    for (int i = 0; i < flightCount; i++)
    {
        if (delFlightID == flights[i].flightID)
        {
            for (int j = i; j < flightCount - 1; j++)
            {
                flights[j] = flights[j + 1];
            }
            flightCount--;
            cout << "Flight deleted successfully\n";
            return;
        }
    }
    cout << "Flight not found\n";
}
void viewFlights()
{
    if (flightCount == 0)
    {
        cout << "\nNo flights currently registered.\n";
        return;
    }

    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "ID    Number    From      To      Fare   Status      Flight Name\n";
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < flightCount; i++)
    {
        cout << flights[i].flightID << "   "
             << flights[i].flightNumber << "    "
             << flights[i].fromLocation << "    "
             << flights[i].destination << "       "
             << flights[i].flightFare << "    "
             << flights[i].status;
        if (flights[i].status == "Full")
        {
            cout << "          ";
        }
        else
        {
            cout << "     ";
        }
        cout << flights[i].flightName << endl;
    }
    cout << "--------------------------------------------------------------------------------\n";
}
