#include "record.h"
#include <iostream>


record::record()
{
	//cout << this << " Record Created" << endl;
}
record::record(string ID,string jobTitle,string emailAddress,string lastName,string firstName,string pNumber,string skills,string country)
{
	this->ID=ID;
	this->jobTitle=jobTitle;
	this->emailAddress=emailAddress;
	this->lastName=lastName;
	this->firstName=firstName;
	this->pNumber=pNumber;
	this->skills=skills;
	this->country=country;
	deepDelete = 1;
	//cout << this << " Record Created" << endl;
}

record::~record()
{
	/*cout << &ID<<" "
		<< &jobTitle << " "
		<< &emailAddress << " "
		<< &lastName << " "
		<< &firstName << " "
		<< &pNumber << " "
		<< &skills << " "
		<< &country << endl;*/
	//cout << this << " Record Deleted" << endl;
}
