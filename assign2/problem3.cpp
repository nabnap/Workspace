
/******************************************************************************
Title: problem3.cpp

Author: Robert Dudasik, Nick Biegel, Ethan Blatti

Created on: October 20th, 2016

Description: A clock program that ticks once every second.

Purpose: Demonstrate knowledge of classes by creating a clock object that displays the time every second.

Usage: Enter the values for hours, minutes, and seconds and the clock will tick every second.

Build with : Visual Studio
******************************************************************************/


#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

//method to clear cin buffer and ignore invalid input
void isIncorrect(){
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Invaid value entered. Please try again." << endl;
}

//Clock class with hours, minutes, seconds, and period (AM/PM)
class Clock{
	int hours;
	int minutes;
	int seconds;
	string period;

//constructors
public: Clock();
		Clock(int, int, int, string);
		//tick method that incremements the time by one second and displays it
		void tick(){
			string sec;
			string min;
			string h;
			seconds++;
			if (seconds == 60){
				minutes++;
				seconds = 0;
			}
			if (minutes == 60){
				hours++;
				minutes = 0;
			}
			if (hours == 24){
				hours = 0;
				period = "AM";
			}
			if (hours >= 12){
				period = "PM";
			}
			if (seconds < 10){
				sec = "0" + to_string(seconds);
			}
			else{
				sec = to_string(seconds);
			}
			if (minutes < 10){
				min = "0" + to_string(minutes);
			}
			else{
				min = to_string(minutes);
			}
			if (hours == 0){
				h = "12";
			}
			else if (hours < 10){
				h = "0" + to_string(hours);
			}
			else if (hours > 12){
				int temp = hours - 12;
				if (temp < 10){
					h = "0" + to_string(temp);
				}
				else{
					h = to_string(temp);
				}
			}
			else{
				h = to_string(hours);
			}

		cout << h << ":" << min + ":" << sec << " " << period << endl;
		}

};

//pause program for one second
void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

//default constructor
Clock::Clock(){
	hours = 0;
	minutes = 0;
	seconds = 0;
	period = "AM";
}

//parameterized constructor
Clock::Clock(int h, int m, int sec, string per){
	hours = h;
	minutes = m;
	seconds = sec;
	period = per;
}

//main method
int main(){
bool valid = false;
int h;
int min;
int sec;
int val;
string period;

//until a valid value for hours is entered, keep asking for a value
while (valid == false){
	cout << "Enter the hour(0-23): " << endl;
	cin >>val;
	if (!cin || val < 0 || val>23){
		isIncorrect();
	}
	else{
		h = val;
		valid = true;
	}
}
valid = false;

//until a valid value for minutes is entered, keep asking for a value
while (valid == false){
	cout << "Enter the minutes(0-59): " << endl;
	cin >> val;
	if (!cin || val < 0 || val>59){
		isIncorrect();
	}
	
	else{
		min = val;
		valid = true;
	}


}
valid = false;

//until a valid value for seconds is entered, keep asking for a value
while (valid == false){
	cout << "Enter the seconds(0-59): " << endl;
	cin >> val;
	if (!cin || val < 0 || val>59){
		isIncorrect();
	}

	else{
		sec = val;
		valid = true;
	}
}

//set period based on hours
if (h > 12){
	period = "PM";
}
else
{
	period = "AM";
}

//create a clock object
Clock c = Clock(h, min, sec, period);

//keep clock ticking infinitely
int n = 1;
while (n == 1){
	
	c.tick();
	wait(1);
}

	return 0;
}
