#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "record.h"
#include "HashTable.h"
#include <string>
#include "linkedlist.h"
#include "ListItem.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

LinkedList* structure;
HashTable* p_NumberTable=NULL;
HashTable* skillsTable=NULL;
HashTable* jobTable=NULL;
HashTable* countryTable=NULL;
void menu();
clock_t startTime;
clock_t endTime;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	structure = new LinkedList();
	menu();
	structure->transfered = 0;

	if (p_NumberTable)
		delete p_NumberTable;
	if (skillsTable)
		delete skillsTable;
	if (jobTable)
		delete jobTable;
	if (countryTable)
		delete countryTable;
	delete structure;
	system("pause");
}

void importLists(){
	std::ios::sync_with_stdio(false);
		string location;
		do {
			cout<< "type location of dataset: ";
			cin >> location;
			if (cin.fail())
				cin.clear();
			if (location.length()<5||location.substr(location.length() - 4) != ".csv") {
				cout << "This File Cannot Be Read, Please enter again" << endl;
				//location = "C:\\ADB\\DS_10_CSV.csv"; //DEBUG 
				location = "D:\\Download\\DS_100k_CSV.csv";
				}
			}while (location.substr(location.length() - 4) != ".csv"|| !ifstream(location));
	ifstream file(location,ios::binary|ios_base::skipws);
	int noOfItems=0;
	string temp;
	while (getline(file, temp))
		noOfItems++;
	cout << noOfItems << endl;
	if (!structure->isEmpty())
	{
		delete structure;
		structure = new LinkedList();
	}
	string* pi = new string[8];
	if (p_NumberTable)
		delete p_NumberTable;
	if (skillsTable)
		delete skillsTable;
	if (jobTable)
		delete jobTable;
	if (countryTable)
		delete countryTable;
	p_NumberTable = new HashTable(noOfItems);
	skillsTable = new HashTable(noOfItems);
	jobTable = new HashTable(noOfItems);
	countryTable = new HashTable(noOfItems);
	int k = 0;
	int loop;
	int FranceCount = 0;
	file.clear();
	file.seekg(0,ios::beg);
	startTime = clock();
	string result;
	stringstream resultstream;
	cout << "import start" << endl;
	while (getline(file, result)) {
		resultstream = stringstream(result);
		for (loop = 0; loop < 8; loop++)
			getline(resultstream, pi[loop], ',');
		record* item = new record(pi[0], pi[1], pi[2], pi[3], pi[4], pi[5], pi[6], pi[7]);
			structure->insertItem(item);
			p_NumberTable->insertRecord(item->pNumber, item);
			skillsTable->insertRecord(item->skills, item);
			jobTable->insertRecord(item->jobTitle, item);
			countryTable->insertRecord(item->country, item);
		k++;
	}
	//system("pause");
	endTime = clock();
	cout << "Time Cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	cout << " No:of data " << k << endl;

	cout << "pre Sort Check" << endl;
	if (structure->isSorted())
		cout << "list Sorted" << endl;
	else
		cout << "list Not Sorted" << endl;
	cout << "sort start" << endl;
	//structure->displayList();
	startTime = clock();
	 structure=structure->quicksort();
	endTime = clock();
	cout << "Time Cost for sorting:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	cout << "display" << endl;
  
	cout << "import completed" << endl;
	delete[] pi;
}

void deletePhoneNumber() {
	string pHomeNumber;
	cin.ignore(0x7FFFFFFF, '\n');
	cout << "Phone Number To be deleted: " << endl;
	getline(cin,pHomeNumber);
	startTime = clock();
	LinkedList* test;
	test = p_NumberTable->getQuery(pHomeNumber);
	if (test) {
		ListItem* current = test->head;
		while (current != NULL)
		{
			record* temRecord=current->data;
			if (current->data->pNumber.compare(pHomeNumber) == 0) {
				p_NumberTable->deleteWithSecondKey(temRecord->pNumber, temRecord->pNumber, 1);
				skillsTable->deleteWithSecondKey(temRecord->skills, pHomeNumber, 1);
				jobTable->deleteWithSecondKey(temRecord->jobTitle, pHomeNumber, 1);
				countryTable->deleteWithSecondKey(temRecord->country, pHomeNumber, 1);
				structure->transfered = 0;
				structure->deepDelete = 1;
				structure->deletePhoneNumber(pHomeNumber);
			}
			current = current->next;
		}
		delete test;
		endTime = clock();
		cout << "Time Cost for deleting" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	}
	else
		cout << "Not Found" << endl;
}
void deleteCountry() {
	string pHomeNumber;
	cin.ignore(0x7FFFFFFF, '\n');
	cout << "Country To be destroyed: " << endl;
	getline(cin, pHomeNumber);
	startTime = clock();
	cout << pHomeNumber << endl;
	LinkedList* test = countryTable->getQuery(pHomeNumber);
	if (test) {
		ListItem* current = test->head;
		while (current != NULL)
		{
			if (current->data->country.compare(pHomeNumber) == 0) {
				p_NumberTable->deleteWithSecondKey(current->data->pNumber, pHomeNumber, 2);
				skillsTable->deleteWithSecondKey(current->data->skills, pHomeNumber, 2);
				jobTable->deleteWithSecondKey(current->data->jobTitle, pHomeNumber, 2);
				countryTable->deleteWithSecondKey(current->data->country, pHomeNumber, 2);
			}
			current = current->next;
		}
		structure->deepDelete = 1;
		structure->transfered = 0;
		structure->deleteCountry(pHomeNumber);
		cout << endl << endl << pHomeNumber << " Nuked" << endl << endl;
		endTime = clock();
		cout << "Time Cost for deleting" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
		delete test;
	}
	else
		cout << "Not Found" << endl;
}
void search() {
	int result=0;
	string key;
	cout << "select a catagory to search" << endl;
	cout << "1: Phone Number" << endl;
	cout << "2:Skills" << endl;
	cout << "3: Job Title" << endl;
	cout << "4: Country" << endl;
	cout << "Others: Exit" << endl;
	cin >> result;
	if (cin.fail())
		cin.clear();
	cin.ignore(0x7FFFFFFF, '\n');
	cout << "Search By: " << endl;
		getline(cin, key);
		LinkedList* queryResult=NULL;
		//ListItem* Current;

	switch (result)
	{
	case(1):
		startTime = clock();
		//cout << "you Inserted: "<<key<<endl;
		queryResult=p_NumberTable->getQuery(key);
		if (queryResult&&!queryResult->isEmpty()) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(1, key);
			cout << "type code to do deeper search" << endl;
			cout << "2: Skills" << endl;
			cout << "3: Job Title" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			if (cin.fail())
				cin.clear();
			cin.ignore(0x7FFFFFFF, '\n');
			switch (result) {
			case 2:
			case 3:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore(0x7FFFFFFF, '\n');
				getline(cin, key);
				queryResult->linearsearchRecord(result, key);
				break;
			default:
				break;
			}
		}
		break;

	case(2):
		startTime = clock();
		queryResult = skillsTable->getQuery(key);
		if (queryResult && !queryResult->isEmpty()) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "3: Job Title" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			if (cin.fail())
				cin.clear();
			cin.ignore(0x7FFFFFFF, '\n');
			switch (result) {
			case 1:
			case 3:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore(0x7FFFFFFF, '\n');
				getline(cin, key);
				queryResult->linearsearchRecord(result, key);
				break;
			default:
				break;
			}
		}
		cout << "Time Cost for searching" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
		cout << endl << endl << "Exit Searching" << endl << endl;
	break;

	case(3):
		startTime = clock();
		queryResult = jobTable->getQuery(key);
		if (queryResult && !queryResult->isEmpty()) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "2: Skills" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			if (cin.fail())
				cin.clear();
			cin.ignore(0x7FFFFFFF, '\n');
			switch (result) {
			case 1:
			case 2:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore(0x7FFFFFFF, '\n');
				getline(cin, key);
				queryResult->linearsearchRecord(result, key);
				break;
			default:
				break;
			}
		}
		cout << "Time Cost for searching" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
		break;


	case(4):
		startTime = clock();
		queryResult = countryTable->getQuery(key);
		if (queryResult && !queryResult->isEmpty()) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "2: Skills" << endl;
			cout << "3: JobTitle" << endl;
			cout << "5: Exit" << endl;
			cin >> result;
			if (cin.fail())
				cin.clear();
			cin.ignore(0x7FFFFFFF, '\n');
			switch (result) {
			case 1:
			case 2:
			case 3:
				cout << "Search By: " << endl;
				cin.ignore(0x7FFFFFFF, '\n');
				getline(cin, key);
				queryResult->linearsearchRecord(result, key);
				break;
			default:
				break;
			}
		}
		cout << "Time Cost for searching" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
		break;
		default:
		cout <<endl<<endl<< "Wrong Answer" << endl << endl ;
		break;
	}

	cout << endl << endl << "End Search" << endl << endl;
	if (queryResult) {
		delete queryResult;
		queryResult = NULL;
	}
}
void menu() {
	bool exit = false;
	int action;
	while (!exit) {
		cout << "-------------------------------------------------------------" << endl;
		cout << "Avalible Operation"<<endl;
		cout << "-------------------------------------------------------------" << endl;
		cout << "1: Import List" << endl;
		if (!structure->isEmpty()) {
			cout << "2: Show Records" << endl;
			cout << "3: Delete a Record By Phone Number" << endl;
			cout << "4: Delete Records By Country" << endl;
			cout << "5: Search Records" << endl;
			cout << "6: Show Number Of Element" << endl;
		}
		cout << "31415926: Exit" << endl;

		cin >> action;
		if (cin.fail())
			cin.clear();
		cout <<endl << "-------------------------------------------------------------" << endl;
		switch (action) {
			case(1):
				importLists();
				if (structure->isSorted())
					cout << "list Sorted" << endl;
				else
					cout << "list Not Sorted" << endl;
			break;
			case(2):
				structure->displayList();
				//countryTable->displayAllRecords();
			break;
			case(31415926):
				exit = true;
				break;
			case(6):
				structure->displayCount();
				structure->last->data->displayRecord();
			break;
			case(3):
				deletePhoneNumber();
				break;
			case(4):
				deleteCountry();
				break;
			case(5):
				search();
				break;
			default:
				cout << "Not Valid" << endl;
				break;
		}
	}
}
