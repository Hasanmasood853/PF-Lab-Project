#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// Structures
struct Flight
{
	int flightID;
	string flightNumber;
	string destination;
	string fromLocation;
	string flightDate;
	string departureTime;
	string arrivalTime;
	int totalSeats;
	int reservedSeats;
	int flightFare;
	string flightName;
	string status;
	string* passengerNames;
	int seatMap[50][6];
};

struct Passenger
{
	string userID;
	string userPass;
	string fullName;
	int flightID;
	int seats;
	string* bookedPassengerNames;
	string bookingStatus;
	double totalFare;
};

// Global Variables
const int maxFlights = 8;
int flightCount = 4;
Flight flights[maxFlights];

int bookingCount = 0;
int passengerCount = 0;
int passengerCapacity = 5;
Passenger* passenger;

string adminPass = "1234";
string adminUser = "admin";

// Function Prototypes
void initializeFlights();
bool adminloginPanel();
int passengerLogin();
void passengerSignUp();//also used by admin to add new passenger
void addFlight();
void removeFlight();
void viewFlights();
void bookFlight(int passengerIndex);
void cancelReservation(int passengerIdx);
void removePassenger();
void viewPassengers();
void updatePassenger();
void updateFlight();
void savePassengerReport();
void searchPassengerReport();
void genPassengerReport(int userIdx);

int main()
{
	system("cls");
	initializeFlights();
	int menuChoice;

	do
	{
		cout << "\n*************************************\n";
		cout << "      Airline Management System        \n";
		cout << "*************************************\n";
		cout << "Are you admin or passenger?\n1.Admin Panel    2.Passenger Panel   3.Exit\n";
		cout << "Enter your choice (1 2 or 3): ";
		cin >> menuChoice;

		while (menuChoice < 1 || menuChoice > 3)
		{
			cout << "Invalid choice! Enter again: ";
			cin >> menuChoice;
		}

		switch (menuChoice)
		{
		case 1:
		{
			cout << "\nHello Admin! Enter your valid credentials to Login";
			if (adminloginPanel())
			{
				bool adminActive = true;
				while (adminActive)
				{
					int adminChoice;
					cout << "\n===== Admin Panel =====\n";
					cout << "1.Change Password\n2.Current Flights & Passengers\n3.Add/Remove Passenger\n4.Update Passenger or Flight Data\n5.Add/Remove Flights\n6.Check reports\n7.Exit\nEnter your choice: ";
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
						viewFlights();
						cout << endl;
						viewPassengers();
						break;
					case 3:
					{
						viewPassengers();
						int addRemPassenger;
						cout << "Choose an option:\n1.Add Passenger\t2.Remove Passenger\nEnter option: ";
						cin >> addRemPassenger;
						while (addRemPassenger != 1 && addRemPassenger != 2)
						{
							cout << "Invalid Choice! Enter again (1 or 2): ";
							cin >> addRemPassenger;
						}
						if (addRemPassenger == 1)
							passengerSignUp();
						else
							removePassenger();
						break;
					}
					case 4: {
						int updateChoice;
						cout << "Choose an option:\n1.Update Passenger\t2.Update Flight\nEnter option: ";
						cin >> updateChoice;
						while (updateChoice != 1 && updateChoice != 2)
						{
							cout << "Invalid Choice! Enter again (1 or 2): ";
							cin >> updateChoice;
						}
						if (updateChoice == 1)
							updatePassenger();
						else
							updateFlight();
					};
						  break;
					case 5:
					{
						int addRemFlight;
						cout << "Choose an option:\n1.Add Flights\t2.Remove Flights\n";
						cin >> addRemFlight;
						while (addRemFlight != 1 && addRemFlight != 2)
						{
							cout << "Invalid Choice! Enter again (1 or 2): ";
							cin >> addRemFlight;
						}
						if (addRemFlight == 1)
							addFlight();
						else
							removeFlight();
						break;
					}
					case 6:
					{
						int reportChoice;
						cout << "Choose an option:\n1.Passenger Report\t2.Flights Report\nEnter Choice: ";
						cin >> reportChoice;
						while (reportChoice != 1 && reportChoice != 2)
						{
							cout << "Invalid Choice! Enter again (1 or 2): ";
							cin >> reportChoice;
						}
						if (reportChoice == 1) {
							savePassengerReport();
							char readChoice;
							cout << "Do you want to read any passenger report (y/n): ";
							cin >> readChoice;
							while (readChoice != 'Y' && readChoice != 'y' && readChoice != 'N' && readChoice != 'n') {
								cout << "Invalid choice! Enter again (y/n): ";
								cin >> readChoice;
							}
							if (readChoice == 'y' || readChoice == 'Y') {
								searchPassengerReport();
							}
						}
						else
							flightsReport();
						break;
					}
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
			int logInIdx = -1;
			do {
				int logSignChoice;
				cout << "\nDo you want to login or sign up\n";
				cout << "1. Login\n2. Sign Up (New User)\n";
				cout << "Enter choice: ";
				cin >> logSignChoice;
				while (logSignChoice != 1 && logSignChoice != 2) {
					cout << "Invalid choice! Enter again (1 or 2): ";
					cin >> logSignChoice;
				}
				if (logSignChoice == 1)
				{
					cout << "\nHello Passenger! Enter your valid credentials to Login\n";
					logInIdx = passengerLogin();
				}
				else if (logSignChoice == 2)
				{
					passengerSignUp();
					cout << "\nPlease Login with your new credentials.\n";
				}
			} while (logInIdx == -1);

			cout << "\nLogin Successful! Welcome " << passenger[logInIdx].fullName << endl;
			bool passengerActive = true;
			while (passengerActive)
			{
				int passengerChoice;
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
					char bookChoice;
					do
					{
						bookFlight(logInIdx);
						cout << "Do you want to book another flight (Y/N): ";
						cin >> bookChoice;
						while (bookChoice != 'y' && bookChoice != 'Y' && bookChoice != 'N' && bookChoice != 'n')
						{
							cout << "Invalid choice! Select (Y/y for yes) or (N/n for no) ";
							cin >> bookChoice;
						}
					} while (bookChoice == 'y' || bookChoice == 'Y');
					break;
				case 2:
					cancelReservation(logInIdx);
					break;
				case 3:
					viewFlights();
					break;
				case 4:
					genPassengerReport(logInIdx);
					break;
				case 5:
					passengerActive = false;
					cout << "Logged out successfully.\n";
					break;
				}
			}
			break;
		}
		case 3:
			cout << "Exiting System. Thank you!\n";
			break;
		}
	} while (menuChoice != 3);

	delete[] passenger;
	return 0;
}

void initializeFlights()
{
	flights[0] = { 101, "EK-502", "DXB", "KHI", "02-10-2023", "10:30 AM", "01:45 PM", 180, 2, 25000, "Emirates", "Available", new string[180]{"Ali Khan", "Sara Ahmed"} };
	flights[1] = { 102, "AB-112", "LHE", "ISB", "03-10-2023", "08:00 AM", "09:00 AM", 150, 1, 12000, "Airblue", "Available", new string[150]{"Bilal Tariq"} };
	flights[2] = { 103, "SA-990", "RUH", "PEW", "02-10-2023", "11:00 PM", "04:30 AM", 200, 1, 45000, "Saudi Air", "Available", new string[200]{"Usman Ghani"} };
	flights[3] = { 104, "PK-301", "KHI", "LHR", "04-10-2023", "02:00 PM", "11:30 PM", 250, 0, 85000, "PIA", "Available", new string[250]{} };
	flightCount = 4;

	passenger = new Passenger[passengerCapacity];
	passenger[0] = { "user1","12341","Hassan", 101, 2, new string[2]{"Ali Khan", "Sara Ahmed"}, "Booked" ,50000 };
	passenger[1] = { "user2","12342","Husnain",102, 1, new string[1]{"Bilal Tariq"}, "Booked",12000 };
	passenger[2] = { "user3","12343","Ahmad", 103, 1, new string[1]{"Usman Ghani"}, "Booked" ,45000 };
	bookingCount = 3;
	passengerCount = 3;

	for (int i = 0; i < flightCount; i++) {
		for (int r = 0; r < 50; r++)
			for (int c = 0; c < 6; c++)
				flights[i].seatMap[r][c] = 0;
	}

	flights[0].seatMap[0][0] = 1;
	flights[0].seatMap[0][1] = 1;
	flights[1].seatMap[0][0] = 1;
	flights[2].seatMap[0][0] = 1;
}

bool adminloginPanel()
{
	string userName, userPass;
	cout << "\nEnter your username: ";
	cin.ignore();
	getline(cin, userName);
	cout << "Enter your password: ";
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

int passengerLogin()
{
	string logUserId, logUserPass;
	cout << "\nEnter your username: ";
	cin.ignore();
	cin >> logUserId;
	cout << "Enter your password: ";
	cin.ignore();
	cin >> logUserPass;
	for (int i = 0; i < passengerCount; i++) {
		if (passenger[i].userID == logUserId && passenger[i].userPass == logUserPass) {
			return i;
		}
	}
	cout << "\nInvalid user ID or Password\n";
	return -1;
}

void passengerSignUp() //also used by admin to add new passenger
{
	if (passengerCount >= passengerCapacity) {
		int newCapacity = passengerCapacity * 2;
		Passenger* newArray = new Passenger[newCapacity];
		for (int i = 0; i < passengerCount; i++) {
			newArray[i] = passenger[i];
		}
		delete[] passenger;
		passenger = newArray;
		passengerCapacity = newCapacity;
	}
	string signUserId, signUserPass, signName;
	bool existId = true;
	cout << "\nAdding new Passenger into system\n";
	cin.ignore();
	while (existId) {
		existId = false;
		cout << "Enter username to register: ";
		getline(cin, signUserId);
		for (int i = 0; i < passengerCount; i++) {
			if (passenger[i].userID == signUserId) {
				cout << "Username already exists! Try another\n";
				existId = true;
				break;
			}
		}
	}
	passenger[passengerCount].userID = signUserId;
	cout << "Enter password to register: ";
	getline(cin, signUserPass);
	passenger[passengerCount].userPass = signUserPass;
	cout << "Enter your full name: ";
	getline(cin, signName);
	passenger[passengerCount].fullName = signName;
	passenger[passengerCount].flightID = 0;
	passenger[passengerCount].seats = 0;
	passenger[passengerCount].bookingStatus = "No Booking";
	cout << "Registration Successful! You can now Login.\n";
	passengerCount++;
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

	cout << "Enter Date (DD-MM-YYYY): ";
	getline(cin, flights[flightCount].flightDate);

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

	for (int r = 0; r < 20; r++) {
		for (int c = 0; c < 5; c++) {
			flights[flightCount].seatMap[r][c] = 0;
		}
	}

	flights[flightCount].passengerNames = new string[flights[flightCount].totalSeats];

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

	cout << "\n-------------------------------------------------------------------------------------\n";
	cout << "ID       Date         Number     From      To        Fare     Status       Flight Name\n";
	cout << "---------------------------------------------------------------------------------------\n";
	for (int i = 0; i < flightCount; i++)
	{
		cout << flights[i].flightID << "    "
			<< flights[i].flightDate << "     "
			<< flights[i].flightNumber << "     "
			<< flights[i].fromLocation << "     "
			<< flights[i].destination << "        "
			<< flights[i].flightFare << "     "
			<< flights[i].status;
		if (flights[i].status == "Full")
		{
			cout << "           ";
		}
		else
		{
			cout << "      ";
		}
		cout << flights[i].flightName << endl;
	}
	cout << "----------------------------------------------------------------------------------------\n";
}

void bookFlight(int passengerIndex)
{
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
	cout << "\n-----------------------------------------------------------------------------------\n";
	cout << "ID      Date        Number     From       To       Fare     Status       Flight Name\n";
	cout << "-------------------------------------------------------------------------------------\n";
	cout << flights[foundIdx].flightID << "    "
		<< flights[foundIdx].flightDate << "     "
		<< flights[foundIdx].flightNumber << "     "
		<< flights[foundIdx].fromLocation << "     "
		<< flights[foundIdx].destination << "        "
		<< flights[foundIdx].flightFare << "     "
		<< flights[foundIdx].status;
	if (flights[foundIdx].status == "Full")
	{
		cout << "           ";
	}
	else
	{
		cout << "      ";
	}
	cout << flights[foundIdx].flightName << endl;

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
		passenger[passengerIndex].flightID = givenFlightID;
		passenger[passengerIndex].seats = seatsNum;
		passenger[passengerIndex].bookingStatus = "Booked";
		if (passenger[passengerIndex].seats > 0) {
			passenger[passengerIndex].bookedPassengerNames = new string[seatsNum];
		}

		passenger[passengerIndex].totalFare = 0;
		cin.ignore();
		for (int k = 0; k < seatsNum; k++)
		{
			string name;
			cout << "Enter name for Pasenger " << k + 1 << " : ";
			getline(cin, name);
			passenger[passengerIndex].bookedPassengerNames[k] = name;
			flights[foundIdx].passengerNames[flights[foundIdx].reservedSeats + k] = name;

			bool seatBooked = false;
			do
			{
				int row, col;
				cout << "Enter seat row no (1-20): ";
				cin >> row;
				while (row < 1 || row > 20)
				{
					cout << "Invalid row Num! Enter again (1-20): ";
					cin >> row;
				}
				cout << "A and B seats are Business Class\n";
				cout << "Enter seat col (1-5) [1=A,2=B,3=C,4=D,5=E]: ";
				cin >> col;
				while (col < 1 || col > 5)
				{
					cout << "Invalid col Num! Enter (1-5) [1=A,2=B,3=C,4=D,5=E]: ";
					cin >> col;
				}
				if (flights[foundIdx].seatMap[row - 1][col - 1] == 0)
				{
					if (col == 1 || col == 2) {
						passenger[passengerIndex].totalFare += flights[foundIdx].flightFare * 1.4;
						cout << "  (Business Class Seat Added)\n";
					}
					else {
						passenger[passengerIndex].totalFare += flights[foundIdx].flightFare;
						cout << "  (Economy Class Seat Added)\n";
					}
					cout << "Seat is available! Booking now...\n";
					flights[foundIdx].seatMap[row - 1][col - 1] = 1;
					seatBooked = true;
				}
				else
				{
					cout << "Sorry! Seat is already taken\n";
				}
			} while (!seatBooked);
		}

		flights[foundIdx].reservedSeats += seatsNum;

		if (flights[foundIdx].reservedSeats >= flights[foundIdx].totalSeats)
		{
			flights[foundIdx].status = "Full";
		}
		cout << "Booking Confirmed for " << passenger[passengerIndex].fullName << endl;
	}
	else
	{
		cout << "Sorry, this flight is fully booked.\n";
	}
}

void cancelReservation(int passengerIdx) {
	if (passenger[passengerIdx].bookingStatus == "No Booking") {
		cout << "No booking found\n";
		return;
	}
	int bookedFID = passenger[passengerIdx].flightID,
		bookedSeats = passenger[passengerIdx].seats;
	cout << endl << passenger[passengerIdx].fullName << " your booking details are:\n1. Booked Flight id: " << bookedFID <<
		"\n2. Seats booked: " << bookedSeats << "\n3. Total Fare: " << passenger[passengerIdx].totalFare << endl;
	cout << "Booked Passenger Names:\n";
	for (int i = 0; i < passenger[passengerIdx].seats; i++) {
		cout << i + 1 << ". " << passenger[passengerIdx].bookedPassengerNames[i] << endl;
	}
	char cancelChoice;
	cout << "\nAre you sure! You want to cancel reservation (Y/N): ";
	cin >> cancelChoice;
	while (cancelChoice != 'Y' && cancelChoice != 'y' && cancelChoice != 'N' && cancelChoice != 'n') {
		cout << "Invalid Choice! Enter (Y/y for Yes , N/n for No): ";
		cin >> cancelChoice;
	}
	if (cancelChoice == 'y' || cancelChoice == 'Y') {
		int foundIdx = -1;
		for (int i = 0; i < flightCount; i++) {
			if (bookedFID == flights[i].flightID) {
				foundIdx = i;
				break;
			}
		}
		if (foundIdx != -1) {
			flights[foundIdx].reservedSeats -= bookedSeats;
			if (flights[foundIdx].status == "full") {
				flights[foundIdx].status = "available";
			}
		}
		passenger[passengerIdx].bookingStatus = "No Booking";
		passenger[passengerIdx].seats = 0;
		passenger[passengerIdx].flightID = 0;
		passenger[passengerIdx].totalFare = 0;
		if (passenger[passengerIdx].bookedPassengerNames != nullptr) {
			delete[] passenger[passengerIdx].bookedPassengerNames;
			passenger[passengerIdx].bookedPassengerNames = nullptr;
		}
		cout << "Reservation cancelled successfully\n";
	}
	else {
		cout << "Reservation is not cancelled! Thanks\n";
	}
}

void viewPassengers() {
	cout << "\nAll passengers details:\n";
	cout << "Total Passengers: " << passengerCount << endl;
	for (int i = 0; i < passengerCount; i++) {
		cout << "\nPassenger " << i + 1 << " details:\n full name: " << passenger[i].fullName << endl
			<< " User Name: " << passenger[i].userID << endl << " Password: " << passenger[i].userPass << endl
			<< " Booking status: " << passenger[i].bookingStatus << endl;
		if (passenger[i].bookingStatus == "No Booking") {
			cout << " Due to no booking No flight ID and other data shown\n";
		}
		else {
			cout << " Booked Flight Id: " << passenger[i].flightID << endl;
			cout << " Seats Booked: " << passenger[i].seats << endl;
			cout << " full name: " << passenger[i].totalFare << endl;
		}
		cout << endl;
	}
}

void removePassenger() {
	string removeUser;
	cin.ignore();
	cout << "\n===== REMOVE PASSENGER =====\n";
	cout << "Enter passenger username to remove: ";
	getline(cin, removeUser);
	int foundUserIdx = -1;
	for (int i = 0; i < passengerCount; i++) {
		if (passenger[i].userID == removeUser) {
			foundUserIdx = i;
			break;
		}
	}
	if (foundUserIdx != -1) {
		if (passenger[foundUserIdx].bookedPassengerNames != nullptr) {
			delete[] passenger[foundUserIdx].bookedPassengerNames;
		}
		for (int j = foundUserIdx; j < passengerCount - 1; j++) {
			passenger[j] = passenger[j + 1];
		}
		passengerCount--;
		cout << "Passenger removed successfully.\n";
	}
	else {
		cout << "Passenger not found.\n";
	}
}

void updatePassenger() {
	cout << "\n======= UPDATE PASSENGER DATA =======\n";
	viewPassengers();
	int userFoundIdx = -1;
	string updateUser;
	cin.ignore();

	do {
		cout << "Enter username to update details: ";
		getline(cin, updateUser);

		for (int i = 0; i < passengerCount; i++) {
			if (passenger[i].userID == updateUser) {
				userFoundIdx = i;
				break;
			}
		}

		if (userFoundIdx == -1) {
			cout << "User Not found! Try another.\n";
		}

	} while (userFoundIdx == -1);

	cout << "Updating " << passenger[userFoundIdx].fullName << " Data:\n";

	string newUserID;
	bool userValid = false;
	while (!userValid) {
		userValid = true;
		cout << "Enter new user ID: ";
		getline(cin, newUserID);

		if (newUserID == passenger[userFoundIdx].userID) {
			cout << "New and old ID cannot be same! Enter again.\n";
			userValid = false;
		}
		else {
			for (int i = 0; i < passengerCount; i++) {
				if (i != userFoundIdx && passenger[i].userID == newUserID) {
					cout << "Username " << newUserID << " is already taken! Try another.\n";
					userValid = false;
					break;
				}
			}
		}
	}
	passenger[userFoundIdx].userID = newUserID;

	cout << "Enter new user password: ";
	getline(cin, passenger[userFoundIdx].userPass);

	cout << "Enter new full name: ";
	getline(cin, passenger[userFoundIdx].fullName);

	char updateBooking;
	cout << "Do you want to update Flight/Seat details? (y/n): ";
	cin >> updateBooking;
	while (updateBooking != 'y' && updateBooking != 'Y' && updateBooking != 'n' && updateBooking != 'N') {
		cout << "Invalid choice! Enter again: ";
		cin >> updateBooking;
	}
	if (updateBooking == 'y' || updateBooking == 'Y') {
		if (passenger[userFoundIdx].bookingStatus == "Booked") {
			cout << "Cancelling old reservation to allow update...\n";
			cancelReservation(userFoundIdx);
		}
		cout << "Launching Booking Panel for new details...\n";
		viewFlights();
		cout << endl;
		bookFlight(userFoundIdx);
	}
	cout << "Passenger Data Updated Successfully\n";
}

void updateFlight() {
	viewFlights();
	cout << "\n======= UPDATE FLIGHT DATA =======\n";
	int updateFlightID, flightFoundIdx = -1;
	do {
		cout << "Enter flight id to update data: ";
		cin >> updateFlightID;
		for (int i = 0; i < flightCount; i++) {
			if (flights[i].flightID == updateFlightID) {
				flightFoundIdx = i;
				break;
			}
		}
		if (flightFoundIdx == -1) {
			cout << "No flight found for this id! Try another:\n ";
		}
	} while (flightFoundIdx == -1);
	int newID; bool isValidID = false;
	cout << "Updating flight " << flights[flightFoundIdx].flightNumber << " Data\n";
	cout << "Enter new Data to Update:\n";
	while (!isValidID) {
		isValidID = true;
		cout << "Flight ID: ";
		cin >> newID;
		if (newID == flights[flightFoundIdx].flightID) {
			cout << "New and old ID cannot be same! Enter again: ";
			isValidID = false;
		}
		else {
			for (int i = 0; i < flightCount; i++) {
				if (i != flightFoundIdx && flights[i].flightID == newID) {
					cout << "ID " << newID << " is already used by another flight!\n";
					isValidID = false;
					break;
				}
			}
		}
	}
	flights[flightFoundIdx].flightID = newID;
	cin.ignore();
	cout << "Flight Name (e.g Airblue): ";
	getline(cin, flights[flightFoundIdx].flightName);

	cout << "Flight Number (e.g EK-502): ";
	getline(cin, flights[flightFoundIdx].flightNumber);

	cout << "Flight Date (DD-MM-YYYY): ";
	getline(cin, flights[flightFoundIdx].flightDate);

	cout << "From Location Code (e.g KHI): ";
	getline(cin, flights[flightFoundIdx].fromLocation);

	cout << "Destination Code (e.g DXB): ";
	getline(cin, flights[flightFoundIdx].destination);

	cout << "Departure Time (e.g 10:30 AM): ";
	getline(cin, flights[flightFoundIdx].departureTime);

	cout << "Arrival Time(e.g 01:45 PM) : ";
	getline(cin, flights[flightFoundIdx].arrivalTime);

	cout << "Total Seats (e.g 180): ";
	cin >> flights[flightFoundIdx].totalSeats;

	cout << "Flight Fare (e.g 50000): ";
	cin >> flights[flightFoundIdx].flightFare;

	cout << "Seats Reserved: ";
	cin >> flights[flightFoundIdx].reservedSeats;
	cin.ignore();
	if (flights[flightFoundIdx].reservedSeats >= flights[flightFoundIdx].totalSeats) {
		flights[flightFoundIdx].status = "Full";
	}
	else {
		flights[flightFoundIdx].status = "Available";
	}
	cout << "Flight Data Updated Successfully\n";
}

void savePassengerReport() {
	ofstream passengerReport("PassengerReport.txt", ios::out | ios::trunc);
	if (passengerReport.is_open()) {
		for (int i = 0; i < passengerCount; i++) {
			passengerReport << passenger[i].userID << " details:\n   Full Name: " << passenger[i].fullName
				<< "\n   Password: " << passenger[i].userPass
				<< "\n   Total Fare: " << passenger[i].totalFare
				<< "\n   Booking Status: " << passenger[i].bookingStatus
				<< "\n   Seats Booked: " << passenger[i].seats
				<< "\n   Booked Flight ID: " << passenger[i].flightID << endl;
			if (passenger[i].seats > 0 && passenger[i].bookedPassengerNames != nullptr) {
				passengerReport << "Passengers booked by this user:\n";
				for (int j = 0; j < passenger[i].seats; j++) {
					passengerReport << "   " << j + 1 << ". " << passenger[i].bookedPassengerNames[j] << endl;
				}
			}
			if (passenger[i].flightID == 0) {
				cout << "No Booking found for this passenger.\n";
				cout << "Total Fare is: 0\n";
			}
			int dateIdx = -1;
			for (int i = 0; i < flightCount; i++) {
				if (flights[i].flightID == passenger[i].flightID) {
					dateIdx = i;
					break;
				}
			}
			if (dateIdx != -1) {
				passengerReport << "   Transaction Date: " << flights[dateIdx].flightDate << "\n";
			}
			else {
				passengerReport << "   Transaction Date: N/A (No Booking)\n";
			}

			passengerReport << "   Total Fare: " << passenger[i].totalFare << "\n";
			passengerReport << "--------------------------------------\n";
		}
	}
	else {
		cout << "File cannot be accessed\n";
	}
	passengerReport.close();
	cout << "Passenger Report saved successfully\n";
}

void searchPassengerReport() {
	string userNameReport;
	cin.ignore();
	cout << "Enter username to read report: ";
	getline(cin, userNameReport);
	ifstream readPassenger("PassengerReport.txt");
	if (readPassenger.is_open()) {
		string line, current = "";
		bool userFound = false;
		while (getline(readPassenger, line)) {
			current += line + "\n";
			if (line.find("--------------------------------------") != string::npos) {
				if (current.find(userNameReport + " details:") != string::npos) {
					cout << "Data found in file\n";
					cout << current;
					userFound = true;
					break;
				}
				current = "";
			}
		}
		if (!userFound) {
			cout << userNameReport << " not found in the report file.\n";
		}
		readPassenger.close();
	}
	else {
		cout << "File cannot be accessed\n";
	}
}

void genPassengerReport(int userIdx) {
	ofstream genPassReport("PassengerGeneratedReport.txt", ios::out | ios::trunc);
	ifstream readPassenger("PassengerReport.txt");
	if (genPassReport.is_open() && readPassenger.is_open()) {
		string line, current = "";
		while (getline(readPassenger, line)) {
			current += line + "\n";
			if (line.find("--------------------------------------") != string::npos) {
				if (current.find(passenger[userIdx].userID + " details:") != string::npos) {
					cout << "Data found in file\n";
					cout << current;
					genPassReport << "Data found in file\n";
					genPassReport << current;
					break;
				}
				current = "";
			}
		}
		cout << "\nPassenger Report saved successfully\n";
		readPassenger.close();
		genPassReport.close();
	}
	else {
		cout << "FIles cannot be accessed\n";
	}
}
