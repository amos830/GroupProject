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
	structure = new LinkedList();
	menu();
	structure->transfered = 0;

	if (!p_NumberTable)
		delete p_NumberTable;
	if (!skillsTable)
		delete skillsTable;
	if (!jobTable)
		delete jobTable;
	if (!countryTable)
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
			if (location.length()<5||location.substr(location.length() - 4) != ".csv") {
				cout << "This File Cannot Be Read, Please enter again" << endl;
				//location = "C:\\ADB\\DS_10K_CSV.csv"; //DEBUG 
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
		structure->emptyList();
	}
	string* pi = new string[8];
	if (!p_NumberTable)
		delete p_NumberTable;
	if (!skillsTable)
		delete skillsTable;
	if (!jobTable)
		delete jobTable;
	if (!countryTable)
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
	startTime = clock();
	 structure=structure->quicksort();
	endTime = clock();
	cout << "Time Cost for sorting:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	cout << "display" << endl;
  
	cout << "import completed" << endl;
	delete[] pi;
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
	cout << "Search By: " << endl;
		cin.ignore();
		getline(cin, key);
		LinkedList* queryResult=NULL;
		//ListItem* Current;
		LinkedList* QueryResult = new LinkedList();

	switch (result)
	{
	case(1):
		startTime = clock();
		//cout << "you Inserted: "<<key<<endl;
		queryResult=p_NumberTable->getQuery(key);
		if (queryResult) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(1, key);
			cout << "type code to do deeper search" << endl;
			cout << "2: Skills" << endl;
			cout << "3: Job Title" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			switch (result) {
			case 2:
			case 3:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore();
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
		if (queryResult) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "3: Job Title" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			switch (result) {
			case 1:
			case 3:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore();
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
		if (queryResult) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "2: Skills" << endl;
			cout << "4: Country" << endl;
			cout << "Others: Exit" << endl;
			cin >> result;
			switch (result) {
			case 1:
			case 2:
			case 4:
				cout << "Search By: " << endl;
				cin.ignore();
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
		if (queryResult) {
			queryResult = queryResult->quicksort();
			endTime = clock();
			queryResult->linearsearchRecord(result, key);
			cout << "type code to do deeper search" << endl;
			cout << "1:	Phone Number" << endl;
			cout << "2: Skills" << endl;
			cout << "3: JobTitle" << endl;
			cout << "5: Exit" << endl;
			cin >> result;
			switch (result) {
			case 1:
			case 2:
			case 3:
				cout << "Search By: " << endl;
				cin.ignore();
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
				break;
			case(4):
				break;
			case(5):
				search();
				break;
			default:
				cout << "Not Valid" << endl;
		}
	}
}
