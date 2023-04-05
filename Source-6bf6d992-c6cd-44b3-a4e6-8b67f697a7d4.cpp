#include <iostream>
#include <fstream>
#include<string>

using namespace std;

class Room
{

private:
	int roomNum;
	int status;
	string firstName, lastName;

	friend class Hotel;
};

class Courtyard : protected Room
{
private:
	static const int courtyardPrice = 125;
	static const int bookable = 70;
	static int booked;
	
public:
	int getBookable() {
		return bookable - booked;
	}

	friend class Hotel;
};

class Scenic : protected Room
{
private:
	static const int scenicPrice = 145;
	static const int bookable = 35;
	static int booked;

public:
	int getBookable() {
		return bookable - booked;
	}

	friend class Hotel;
};

class DeluxeSuite : protected Room
{
private:
	static const int deluxeSuitePrice = 350;
	static const int bookable = 15;
	static int booked;

public:
	int getBookable() {
		return bookable - booked;
	}

	friend class Hotel;
};

class Penthouse : protected Room
{
private:
	static const int penthousePrice = 1135;
	static const int bookable = 2;
	static int booked;

public:
	int getBookable() {
		return bookable - booked;
	}

	friend class Hotel;
};

int Courtyard::booked = 0;
int Scenic::booked = 0;
int DeluxeSuite::booked = 0;
int Penthouse::booked = 0;

class Hotel
{

private:
	int a, b, c, d;
	int month;
	int	day;
	Courtyard courtyard[70];
	Scenic scenic[35];
	DeluxeSuite deluxeSuite[15];
	Penthouse penthouse[2];
	int dayRevenue;

public:
	void homeMenu();
	void book();
	void showSales();
	void setDate();
	void changeDate();
	void createFile();
	void openFile(int, int);

	Hotel() {

		a = b = c = d = 0;

		for (int i = 101; i < 171; i++) {
			courtyard[i - 101].roomNum = i;
			courtyard[i - 101].status = 0;
		}
		
		for (int i = 201; i < 236; i++) {
			scenic[i - 201].roomNum = i;
			scenic[i - 201].status = 0;
		}

    	for (int i = 236; i < 251; i++) {
    		deluxeSuite[i - 236].roomNum = i;
			deluxeSuite[i - 236].status = 0; 
    	}
    
    	for (int i = 301; i < 303; i++) {
    		penthouse[i - 301].roomNum = i;
			penthouse[i - 301].status = 0;
    	}
	}
};

void Hotel::homeMenu()
{
	int choice = 0;
	bool reserve = false;

	while (choice != 4) {
	std::cout << R"(  
	+-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+
	|H|o|t|e|l| |S|a|n| |D|i|e|g|o|
	+-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+
)";

	cout << "\t1.Book A Room" << endl;
	cout << "\t2.Total Sales" << endl;
	cout << "\t3.Change Date" << endl;
	cout << "\t4.Exit" << endl;
	cout << "\t+-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+" << endl;
	cout << "\nEnter your choice: " << endl;
	cin >> choice;

		switch (choice)
		{
			case 1: book();
				break;
			case 2: showSales();
				break;
			case 3: createFile();
					changeDate();
				break;
			case 4: createFile();
				return;
				break;
			default:
			{
				cout << "\nMake sure you typed correct choice" << endl;;
			}
		}
	}
}

void Hotel::createFile() {
	fstream reservations;
	string fileName = "reservations" + to_string(month) + "-" + to_string(day);
	cout << fileName << "Hello " << endl;
	fileName += ".txt";
	reservations.open(fileName, ios::out);

	if (!reservations) {
		cout << "File does not exist.";
	}
	else {
		cout << "File created." << endl;
		reservations << month << " " << day << endl;
		reservations << a << " " << b << " " << c << " " << d << endl;
		int revenue = 0;
		int added = 0;
		
		for (int i = 0; added < a; i++) {
			if (courtyard[i].status == 1) {
				reservations << courtyard[i].roomNum << " ";
				reservations << courtyard[i].firstName << " ";
				reservations << courtyard[i].lastName << " ";
				reservations << courtyard[i].courtyardPrice << endl;
				revenue += courtyard[i].courtyardPrice;
				added++;
			}
		}added = 0;

		for (int i = 0; added < b; i++) {
			if (scenic[i].status == 1) {
				reservations << scenic[i].roomNum << " ";
				reservations << scenic[i].firstName << " ";
				reservations << scenic[i].lastName << " ";
				reservations << scenic[i].scenicPrice << endl;
				revenue += scenic[i].scenicPrice;
				added++;
			}
		}added = 0;

		for (int i = 0; added < c; i++) {
			if (deluxeSuite[i].status == 1) {
				reservations << deluxeSuite[i].roomNum << " ";
				reservations << deluxeSuite[i].firstName << " ";//
				reservations << deluxeSuite[i].lastName << " ";
				reservations << deluxeSuite[i].deluxeSuitePrice << endl;
				revenue += deluxeSuite[i].deluxeSuitePrice;
				added++;
			}
		}added = 0;

		for (int i = 0; added < d; i++) {
			if (penthouse[i].status == 1) {
				reservations << penthouse[i].roomNum << " ";
				reservations << penthouse[i].firstName << " ";
				reservations << penthouse[i].lastName << " ";
				reservations << penthouse[i].penthousePrice << endl;
				revenue += penthouse[i].penthousePrice;
				added++;
			}
		}reservations << revenue << endl;
	reservations.close();
	}
}

void Hotel::openFile(int month, int day) {
	fstream reservations;
	string fileName = "reservations" + to_string(month) + "-" + to_string(day);
	fileName += ".txt";
	reservations.open(fileName, ios::in);

	if (!reservations) {
		cout << "No such file";
	}
	else {
		
		bool found = false;

		while (!found && !reservations.eof()) {

			int fileMonth, fileDay;
			reservations >> fileMonth >> fileDay;
			reservations >> a >> b >> c >> d;

			if (fileMonth == month && fileDay == day) {
				found = true;
				int added = 0; // is to keep track num of people read in from the file to put in hotel.
				int readRoonNum;
				int sum = 0;
				int sumTemp;

				for (int i = 0; i < a; i++) {
					reservations >> readRoonNum;
					reservations >> courtyard[readRoonNum - 101].firstName;
					reservations >> courtyard[readRoonNum - 101].lastName;		
					reservations >> sumTemp; 
					sum += sumTemp;
					courtyard[readRoonNum - 101].status = 1;
					courtyard[readRoonNum - 101].booked++;
					added++;
				}added = 0;

				for (int i = 0; i < b; i++) {
					reservations >> readRoonNum;
					reservations >> scenic[readRoonNum - 201].firstName;
					reservations >> scenic[readRoonNum - 201].lastName;
					reservations >> sumTemp;
					sum += sumTemp;
					scenic[readRoonNum - 201].status = 1;
					scenic[readRoonNum - 201].booked++;
					added++;
				}added = 0;

				for (int i = 0; i < c; i++) {
					reservations >> readRoonNum;
					reservations >> deluxeSuite[readRoonNum - 236].firstName;
					reservations >> deluxeSuite[readRoonNum - 236].lastName;
					reservations >> sumTemp;
					sum += sumTemp;
					deluxeSuite[readRoonNum - 236].status = 1;
					deluxeSuite[readRoonNum - 236].booked++;
					added++;
				}added = 0;

				for (int i = 0; i < d; i++) {
					reservations >> readRoonNum;
					reservations >> penthouse[readRoonNum - 301].firstName;
					reservations >> penthouse[readRoonNum - 301].lastName;
					reservations >> sumTemp;
					sum += sumTemp;
					penthouse[readRoonNum - 301].status = 1;
					penthouse[readRoonNum - 301].booked++;
					added++;
				} dayRevenue = sum;
				reservations >> dayRevenue;
			}
			else {
				string temp;
				for (int i = 0; i < a + b + c + d; i++) {		
					//this is for reading in the names of the people who booked for rooms.
					//But not for the day we want.
					reservations >> temp;
					reservations >> temp;
					reservations >> temp;
					reservations >> temp;
				}reservations >> temp;
			}
		}
		if (!found) {	
			cout << "The date isn't in the system yet" << endl;
			a = b = c = d = 0;
		}
	}
reservations.close();
}

void Hotel::setDate() {

	string date;
	char delimiter = '/';

	cout << "Enter today's date you would like to book (mm/dd): ";
	cin >> date;

	month = stoi(date.substr(0, 2));
	day = stoi(date.substr(3, 2));
}

void Hotel::changeDate() {

	string date;
	char delimiter = '/';

	cout << "Change date (mm/dd): ";
	cin >> date;

	month = stoi(date.substr(0, 2));
	day = stoi(date.substr(3, 2));

	for (int i = 0; i < a; i++) {
		 courtyard[i].status = 0;
		 courtyard[i].booked = 0;
	}

	for (int i = 0; i < b; i++) {
		scenic[i].status = 0;
		scenic[i].booked = 0;
	}

	for (int i = 0; i < c; i++) {
		deluxeSuite[i].status = 0;
		deluxeSuite[i].booked = 0;
	}

	for (int i = 0; i < d; i++) {
		penthouse[i].status = 0;
		penthouse[i].booked = 0;
	}

	a = b = c = d = 0;
	openFile(month,day);
}

void Hotel::book()
{
	int choice;
	string fName, lName;

	cout << "First name : ";
	cin >> fName;
	cout << "Last name : ";
	cin >> lName;

	cout << "\nWhich room would you like to book?" << endl;
	cout << "\n1.Standard Rooms, Courtyard $125 a night - Rooms 101 thru 170" << endl;
	cout << courtyard[a].getBookable() << " room(s) available" << endl;
	cout << courtyard[a].booked << " room(s) booked" << endl;

	cout << "\n2.Standard Room, Scenic $145 a night - Rooms 201 thru 235" << endl;
	cout << scenic[b].getBookable() << " room(s) available" << endl;
	cout << scenic[b].booked << " room(s) booked" << endl;

	cout << "\n3.Deluxe Suite $350 a night - Rooms 236 thru 250" << endl;
	cout << deluxeSuite[c].getBookable() << " room(s) available" << endl;
	cout << deluxeSuite[c].booked << " room(s) booked" << endl;

	cout << "\n4.Penthouse $1135 a night - Rooms 301 and 302" << endl;
	cout << penthouse[d].getBookable() << " room(s) available" << endl;
	cout << penthouse[d].booked << " room(s) booked" << endl;

	cout << "\nEnter Your Choice: " << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		if (a < 70 && courtyard[a].status == 0) {
			courtyard[a].status = 1;
			courtyard[a].booked++;
			courtyard[a].firstName = fName;
			courtyard[a].lastName = lName;
			a++;
			cout << "\nStandard Rooms, Courtyard room no " << courtyard[a - 1].roomNum << " is booked." << endl;
			cout << "Name " << courtyard[a - 1].firstName << " " << courtyard[a - 1].lastName << endl;
		} else {
			cout << "\nThe room is full." << endl;
		}				
		break;

	case 2:
		if (b < 35 && scenic[b].status == 0) {
			scenic[b].status = 1;
			scenic[b].booked++;
			scenic[b].firstName = fName;
			scenic[b].lastName = lName;
			b++;
			cout << "\n2.Standard Room, Scenic room no " << scenic[b - 1].roomNum << " is booked." << endl;
			cout << "Name " << scenic[b - 1].firstName << " " << scenic[b - 1].lastName << endl;
		} else {
			cout << "\nNo vacancy" << endl;
		}		
		break;

	case 3:
		if (c < 15 && deluxeSuite[c].status == 0) {
			deluxeSuite[c].status = 1;
			deluxeSuite[c].booked++;
			deluxeSuite[c].firstName = fName;
			deluxeSuite[c].lastName = lName;
			c++;
			cout << "\n3.Deluxe Suite room no " << deluxeSuite[c - 1].roomNum << " is booked." << endl;
			cout << "Name " << deluxeSuite[c - 1].firstName << " " << deluxeSuite[c - 1].lastName << endl;
		} else {
			cout << "\nNo vacancy" << endl;
		}		
		break;

	case 4:
		if (d < 2 && penthouse[d].status == 0) {
			penthouse[d].status = 1;
			penthouse[d].booked++;
			penthouse[d].firstName = fName;
			penthouse[d].lastName = lName;
			d++;
			cout << "\nPenthouse room no " << penthouse[d - 1].roomNum << " is booked." << endl;
			cout << "Name: " << penthouse[d - 1].firstName << " " << penthouse[d - 1].lastName << endl;
		} else {
			cout << "\nNo vacancy" << endl;
		}		
		break;

	case 5: break;
		default:
		{
			cout << "Make sure you typed correct choice";
		}
	}
}

void Hotel::showSales()
{
	char toMain;
	int courtyardSales = Courtyard::courtyardPrice * a;
	int scenicSales = Scenic::scenicPrice * b;
	int deluxeSuiteSales = DeluxeSuite::deluxeSuitePrice *c;
	int penthouseSales = Penthouse::penthousePrice * d;
	int totalSales = courtyardSales + scenicSales + deluxeSuiteSales + penthouseSales;

	cout << "\t+-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+-" << endl;
	cout << "\tTotal rooms availability & sales" << endl;
	cout << "\t+-+-+-+-+-+ +-+-+-+ +-+-+-+-+-+-" << endl;

	cout << "\nStandard Rooms, Courtyard" << endl;
	cout << courtyard[a].getBookable() << " room(s) available" << endl;
	cout << courtyard[a].booked << " room(s) booked" << endl;
	cout << "Sales $" << courtyardSales << endl;

	cout << "\nStandard Room, Scenic" << endl;
	cout << scenic[b].getBookable() << " room(s) available" << endl;
	cout << scenic[b].booked << " room(s) booked" << endl;
	cout << "Sales $" << scenicSales << endl;

	cout << "\nDeluxe Suite" << endl;
	cout << deluxeSuite[c].getBookable() << " room(s) available" << endl;
	cout << deluxeSuite[c].booked << " room(s) booked" << endl;
	cout << "Sales $" << deluxeSuiteSales << endl;

	cout << "\nPenthouse" << endl;
	cout << penthouse[d].getBookable() << " room(s) available" << endl;
	cout << penthouse[d].booked << " room(s) booked" << endl;
	cout << "Sales $" << penthouseSales << endl;

	cout << "\nTotal Sales $" << totalSales << endl;

	cout << "\nMAIN MENU(y)| QUIT(n)" << endl;
	cin >> toMain;

	if (toMain == 'y') {
		homeMenu();
	}
	else if (toMain == 'n') {
		return;
	}
}	

int main()
{

	Hotel h;
	h.setDate();
	h.homeMenu();

}
