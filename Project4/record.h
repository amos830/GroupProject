#pragma once
#include <string>
using namespace std;
class record
{
public:
	record();
	record(string ID, string jobTitle, string emailAddress, string lastName, string firstName, string pNumber, string skills, string country);
	~record();
	string ID;
	string jobTitle;
	string emailAddress;
	string lastName;
	string firstName;
	string pNumber;
	string skills;
	string country;
	bool deepDelete;
};

