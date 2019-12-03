#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "record.h"
#include <string>
#include "linkedlist.h"
#include <stdlib.h>  
#include <crtdbg.h>  
using namespace std;
int main() {
	{
	std::ios_base::sync_with_stdio(false);
	//ifstream file("C:\\Windows\\en-US\\DS_100K_csv.csv");
	ifstream file("D:\\Download\\DS_100K_csv.csv");
	InventoryList* test = new InventoryList();
	test->sortCount = 0;
	string* pi = new string[8];
	int k = 0;
	int lastchar = 0;
	int loop;
	file.seekg(ios::beg);
	clock_t startTime = clock();
	string result;
	stringstream resultstream;
	record temp;
	while (getline(file, result)) {
		resultstream = stringstream(result);
		for (loop = 0; loop < 8; loop++)
			getline(resultstream, pi[loop], ',');
		/*lastchar = 0;
		loop = 0;
		for (int l = 0; l < pi->size(); l++) {
			if (result[l] == ','||l==pi->size()-1)
			{
				pi[loop] = result.substr(lastchar,l);
				lastchar = l + 1;
				loop++;
			}
		}*/
		test->insertItem(new record(pi[0], pi[1], pi[2], pi[3], pi[4], pi[5], pi[6], pi[7]));
		k++;
	}
	//system("pause");
	clock_t endTime = clock();
	cout << "Time Cost: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	cout << " No:of data " << k << endl;
	test->displayList();
	cout << "sort start" << endl;
	startTime = clock();
	//InventoryList* sorted = test->quicksort();
	test = test->quicksort();
	endTime = clock();
	cout << "Time Cost for sorting:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	cout << "display" << endl;
	test->displayList();
	cout << "completed" << endl;
	//cout << sorted->transfered << endl;
	//delete sorted;
	cout << "sorted deleted " <<test->transfered<< endl;
	test->markDeepDelete();
	test->~InventoryList();
	cout << "list deleted" << endl;
	delete[] pi;
	}
	//system("pause");
	//_CrtDumpMemoryLeaks();
}