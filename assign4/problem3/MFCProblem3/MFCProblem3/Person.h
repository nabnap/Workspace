#pragma once
#include "stdafx.h"
#include "Person.h"

#include <iostream>
#include <string>
#include <map>


using namespace std;

//create a class for a person
class person {
public:
	string name;
	person(string);
	void set_values(string, string, string, string, string);
	string printRecord();
private:
	string street_number;
	string street;
	string city;
	string state;
	string zipcode;
};





