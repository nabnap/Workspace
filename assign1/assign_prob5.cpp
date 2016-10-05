/******************************************************************************
Title:				assign_prob5.cpp
Author:				Ethan Blatti, Nick Biegel, Robert Dudasik
Created on:			October 4, 2016
Description:		Call a function through a pointer to verify that it works.
Purpose:			To verify that ascVal() works when called through a pointer.
Usage:				Run the program to verify that ascVal() determines the ASCII value of a character.
Build with:			Visual Studio 2015
Modifications:		None
******************************************************************************/
#include <iostream>
#include <cstring>

using namespace std;

//Return the ASCII value of the char
int ascVal(size_t ip, const char* p)
{
	cout << "The length of the string is: "<<strlen(p) << endl;
	if (!p || ip >= strlen(p)) {
		return  -1;
	} else {
		return p[ip];
	}
}

int main() {
	//create pointer to function
	int(*value)(size_t, const char*);
	value = &ascVal;

	//create array of characters to test
	char pchar[]{"This is a test string."};

	//call the pointer to the function and generate output
	cout << "The ascii value of " << pchar[21] << " is: " << value(21, pchar) << endl;

	system("PAUSE");
	return 0;
}
