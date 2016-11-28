#include "stdafx.h"
#include "Person.h"

#include <iostream>
#include <string>
#include <map>






//create constructor
person::person(string name) {
	this->name = name;
}
//create the set_values method
void person::set_values(string _street_number, string _street, string _city, string _state, string _zipcode) {
	this->street_number = _street_number;
	this->street = _street;
	this->city = _city;
	this->state = _state;
	this->zipcode = _zipcode;
}
//create print record method
string person::printRecord() {
	string res;
	res = "\nName: " + this->name + "\nAddress: " + this->street_number + " " + this->street + "\n" + this->city + ", " + this->state + ", " + this->zipcode + "\n";
	return res;
}


