#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#pragma warning(disable : 4996)   // disable warning error
using namespace std;

void DisplayMenu() {
	cout << setfill('*') << setw(26) << "" << endl;
	cout << setfill(' ');
	cout << setw(25) << left << "* 1 - Add One Hour";
	cout << "*" << endl;
	cout << setw(25) << left << "* 2 - Add One Minute";
	cout << "*" << endl;
	cout << setw(25) << left << "* 3 - Add One Second";
	cout << "*" << endl;
	cout << setw(25) << left << "* 4 - Exit Program";
	cout << "*" << endl;
	cout << setfill('*') << setw(26) << "" << endl;
}

string StringConverter(int hour, int minute, int second, string meridian = "none") { // converts the time to a string
	string theTime = "";
	if (hour < 10) {
		theTime = "0" + to_string(hour);
	}
	else {
		theTime = to_string(hour);
	}
	if (minute < 10) {
		theTime = theTime + ":0" + to_string(minute);
	}
	else {
		theTime = theTime + ":" + to_string(minute);
	}
	if (second < 10) {
		theTime = theTime + ":0" + to_string(second);
	}
	else {
		theTime = theTime + ":" + to_string(second);
	}
	if (meridian != "none") {
		theTime = theTime + " " + meridian;
	}
	return theTime;
}

void DisplayClock(int user12Hour, int user12Min, int user12Second, string meridian, int user24Hour, int user24Min, int user24Sec) {
	string clockLabel = "12-Hour Clock";
	string clockLabel24 = "24-Hour Clock";
	string time12 = StringConverter(user12Hour, user12Min, user12Second, meridian);
	string time24 = StringConverter(user24Hour, user24Min, user24Sec);
	int clockLen = clockLabel.length() + (25 - clockLabel.length()) / 2;

	cout << setfill('*') << setw(26) << "";
	cout << "     " << setw(26) << "" << endl;
	cout << setfill(' ') << "*";
	cout << setw(clockLen) << right << clockLabel;
	cout << setw(6) << right << "*" << "     *";
	cout << setw(clockLen) << right << clockLabel24;
	cout << setw(6) << right << "*" << endl;
	cout << "*";
	cout << setw(18) << time12;
	cout << setw(7) << right << "*" << "     *";
	cout << setw(16) << time24;
	cout << setw(9) << right << "*" << endl;
	cout << setfill('*') << setw(26) << "";
	cout << "     " << setw(26) << "" << endl;
}

int TimeConverter(int userHr) {

	if (userHr > 12) {  // if time is PM
		userHr %= 12;
	}
	if (userHr == 00) { // if time is Midnight
		userHr = 12;
	}
	return userHr;
}

void AddHour(int& hours12, int& hours24, string& meridian) {
	if ((hours12 == 11) && (meridian == "P M")) { // changes meridian at midnight
		meridian.at(0) = 'A';
	}
	else if ((hours12 == 11) && (meridian == "A M")) { // changes meridian at noon
		meridian.at(0) = 'P';
	}
	if (hours12 == 12) {
		hours12 = 1;
	}
	else {
		hours12 = hours12 + 1;
	}
	if (hours24 == 23) {
		hours24 = 0;
	}
	else {
		hours24 = hours24 + 1;
	}
	
}


void ClockLoop() {
	time_t now;         //get variables for local time
	struct tm nowLocal;
	now = time(NULL);
	nowLocal = *localtime(&now);    
    int hours24 = nowLocal.tm_hour;
	int minutes24 = nowLocal.tm_min;
	int seconds24 = nowLocal.tm_sec;
	int hours12 = TimeConverter(hours24);
	int minutes12 = nowLocal.tm_min;
	int seconds12 = nowLocal.tm_sec;
	string meridian = "";
	int userChoice;

	if (hours24 < 12) {   // set 12-hour time to AM or PM
		meridian = "A M";
	}
	else {
		meridian = "P M";
	}
	while (true) {
		system("CLS");  // clear screen
		DisplayClock(hours12, minutes12, seconds12, meridian, hours24, minutes24, seconds24);

		DisplayMenu();

		cin >> userChoice;
		if (userChoice == 1) {   // add an hour
			AddHour(hours12, hours24, meridian);

		}
		if (userChoice == 2) {   // add a minute
			if (minutes12 == 59) {
				minutes12 = 0;
				minutes24 = 0;
				AddHour(hours12, hours24, meridian);
			}
			else {
				minutes12 = minutes12 + 1;
				minutes24 = minutes24 + 1;
			}
		}
		if (userChoice == 3) {   // add a second
			if (seconds12 == 59) {
				seconds12 = 0;
				seconds24 = 0;
				if (minutes12 == 59) {
					minutes12 = 0;
					minutes24 = 0;
					AddHour(hours12, hours24, meridian);
				}
				else {
					minutes12 = minutes12 + 1;
					minutes24 = minutes24 + 1;
				}
			}
			else {
				seconds12 = seconds12 + 1;
				seconds24 = seconds24 + 1;
			}
		}

		if (userChoice == 4) {   // break out of loop
			break;
		}
	}
}

