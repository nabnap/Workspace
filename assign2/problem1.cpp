/******************************************************************************
Title:				problem1.cpp
Author:				Ethan Blatti, Nick Biegel, Robert Dudasik
Created on:			October 14, 2016
Description:		A phone book that allows a user to add, delete, and lookup entries
Purpose:			Demonstrate knowledge of classes by using classes to create a phone book directory
Usage:				Select an option listed and manipulate the phone book as needed.
Build with:			Visual Studio 2015
Modifications:		None
******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//================= Entry =================//
//Entry class declaration
class Entry {
public:
	Entry(string, string);
	string getName();
	string getNumber();
private:
	string name, number;
};
//Entry class definition
//Entry constructor
Entry::Entry(string ename, string enumber) {
	name = ename;
	number = enumber;
}
//Returns the name of the entry
string Entry::getName() {
	return name;
}
//Returns the number of the entry
string Entry::getNumber() {
	return number;
}
//============================================//





//================= Book =================//
//Book class declaration
class Book {
public:
	Book() {};
	void add(string,string);
	vector<Entry> getAll();
	vector<Entry> getName(string);
	Entry getNumber(string);
	bool deleteName(string);
	bool deleteNumber(string);
private:
	vector<Entry> entryVec;
};
//Book class definition
//Returns the entry book entries
vector<Entry> Book::getAll() {
	return entryVec;
};

//Delete entry by number
bool Book::deleteNumber(string n) {
	for (unsigned int i = 0; i < entryVec.size(); i++) {
		Entry e = entryVec.at(i);
		if (e.getNumber() == n) {
			entryVec.erase(entryVec.begin() + i);
			return true;
		}
	}
	return false;
};

//Delete entry by name
bool Book::deleteName(string n) {
	vector<Entry> tmp;
	bool removed = false;
	for (unsigned int i = 0; i < entryVec.size(); i++) {
		Entry e = entryVec.at(i);
		if (e.getName() == n) {
			entryVec.erase(entryVec.begin() + i);
			removed = true;
			i == 0 ? 0 : i--;
		}
	}
	return removed;
};

//Get entry by number
Entry Book::getNumber(string n) {
	for (Entry e : entryVec) {
		if (e.getNumber() == n) {
			return e;
		}
	}
	return Entry("","");
};

//Get entry by name
vector<Entry> Book::getName(string n) {
	vector<Entry> tmp;
	for (Entry e : entryVec) {
		if (e.getName() == n) {
			tmp.push_back(e);
		}
	}
	return tmp;
};

//Add entry to the book vector
void Book::add(string name, string number) {
	entryVec.push_back(Entry(name, number));
};
//============================================//





//================= UIManager =================//
//UIManager class declaration
class UIManager {
public:
	UIManager() { invalid = false; };
	void start();
	void displayMenu();
	void addEntry();
	void getEntriesByName();
	void getEntryByNumber();
	void deleteEntriesByName();
	void deleteEntryByNumber();
	void listAllEntries();
private:
	Book book;
	bool invalid;
};
//UIManager class definition
//Runs the UI from start to end
void UIManager::start() {
	char input;
	do{
		//Display the menu
		displayMenu();

		//Grab the first character of the input stream, ignore the rest.
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max() - 1,'\n');
		
		//Clear the console for a clean user UX
		system("cls");

		//Do the correct option for the letter entered
		switch (input) {
		case 'A': addEntry(); break;
		case 'D': deleteEntriesByName();  break;
		case 'G': getEntriesByName(); break;
		case 'L': listAllEntries(); break;
		case 'd': deleteEntryByNumber(); break;
		case 'g': getEntryByNumber(); break;
		case 'Q': return;
		default: invalid = true;
		}
	} while (true);
}

//UI for deleting entry by name
void UIManager::deleteEntriesByName() {
	cout << "===== Delete entries by name =====" << endl << endl;
	string n;
	bool res;

	cout << "Enter name of entries to be deleted: ";
	getline(cin, n);

	res = book.deleteName(n);
	if (res)
		cout << "Entries with the name " << n << " have been deleted from your phonebook." << endl << endl;
	else
		cout << "Nothing with the name " << n << " was found in your phonebook." << endl << endl;

	system("PAUSE");
	system("cls");
}

//UI for deleting entry by number
void UIManager::deleteEntryByNumber() {
	cout << "===== Delete a entry by number =====" << endl << endl;
	string n;
	bool res;

	cout << "Enter number of entry to be deleted: ";
	getline(cin, n);

	res = book.deleteNumber(n);
	if (res)
		cout << "Entry with the number " << n << " has been deleted from your phonebook." << endl << endl;
	else
		cout << "Nothing with the number " << n << " was found in your phonebook." << endl << endl;

	system("PAUSE");
	system("cls");
}

//UI for getting entry by number
void UIManager::getEntryByNumber() {
	cout << "===== Get name by number =====" << endl << endl;
	string n;

	cout << "Enter number: ";
	getline(cin, n);

	Entry e = book.getNumber(n);
	if (e.getName() != "")
		cout << "The name that corresponds to the number " << n << " is \"" << e.getName()<< "\"." << endl  << endl;
	else
		cout << "No name was found for " << n << "." << endl << endl;
	
	system("PAUSE");
	system("cls");
}

//UI for getting entry by name
void UIManager::getEntriesByName() {
	cout << "===== Get numbers by name =====" << endl << endl;
	string n;

	cout << "Enter name: ";
	getline(cin, n);

	//system("cls");

	cout << "Numbers for the name " << n << "..." << endl << endl;
	for (Entry e : book.getName(n)) {
		cout << "Number: " << e.getNumber() << endl;
	}
	cout << endl;
	system("PAUSE");
	system("cls");
}

//UI for listing all entries
void UIManager::listAllEntries() {
	cout << "===== Get all entries in phonebook =====" << endl << endl;
	for (Entry e : book.getAll()) {
		cout << "Name  : " << e.getName() << endl 
			 << "Number: " << e.getNumber() << endl << endl;
	}
	system("PAUSE");
	system("cls");
}

//UI for adding entry
void UIManager::addEntry() {
	cout << "===== Add entry to phonebook =====" << endl << endl;
	string name, number;

	cout << "Persons Name: ";
	getline(cin, name);
	cout << "Persons Number: ";
	getline(cin, number);
	book.add(name,number);

	system("cls");
}

//Displays the main menu to user
void UIManager::displayMenu() {
	cout << "Welcome to your phonebook!" << endl;
	cout << "Select an option from below to perform it." << endl;
	cout << "	A to add an entry" << endl;
	cout << "	D to delete an entry for a name" << endl;
	cout << "	G to get entries for a name" << endl;
	cout << "	L to list entries" << endl;
	cout << "	d to delete an entry for a number" << endl;
	cout << "	g to get the entry for a number" << endl;
	cout << "	Q to Quit" << endl;
	if (invalid) {
		cout << "Invalid input value. Please try again." << endl;
		invalid = false;
	}
}
//============================================//



//Main
int main() {
	//Created UIManager object and start 
	UIManager uim;
	uim.start();
	return 0;
}

