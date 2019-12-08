#include "HashTable.h"
#include <string>
#include <iostream>
#define FNV_32_PRIME 16777619
#define FNV_32_BASIS 2166136261
#define LOAD_FACTOR  1.2
using namespace std;

HashTable::HashTable(int size)
{
	this->size = ((int)(size * 1.2)) < 65535 ? 65535 : ((int)(size*1.2));
	bitRequired= (((int)log2(((double)(this->size))) + 1) < 16 ? 16 : ((int)log2(((double)(this->size)))) + 1);	// set max num of bits the hash value store
	hashTableArray = new LinkedList * [(int)pow(2,bitRequired)];
	this->size = (int)pow(2, bitRequired);
	for (int i = 0; i < this->size; i++)
	{
		hashTableArray[i] = NULL;
	}
}


HashTable::~HashTable()
{
	for (int i = 0; i <size;i++)
	{
		if (hashTableArray[i]!=NULL)
		{
			hashTableArray[i]->transfered=1;
			delete hashTableArray[i];
		}
	}
}

unsigned long int HashTable::FNV_1aHash(string key)
{
	unsigned long int hval = FNV_32_BASIS;
	for (char value : key) {
		hval ^= value;
		hval *= FNV_32_PRIME;
	}
	unsigned long int mask = (((unsigned long int)1 << (bitRequired)) - 1);
	hval= (hval >> bitRequired) ^ (hval & mask);
	return hval;
}
void HashTable::insertRecord(string key, record* value)
{
	unsigned long int hashValue=FNV_1aHash(key);
	/*if(FNV_1aHash(key)== FNV_1aHash("Zimbabwe"))
		cout << "Hashing for "<<key<<" Table Finished For " << value->pNumber <<" With a Hash Value of "<<hashValue<<endl; //DEBUG*/
	if (hashTableArray[hashValue] == NULL)
		{
			hashTableArray[hashValue] = new LinkedList();
		}
	hashTableArray[hashValue]->insertItem(value);
}
LinkedList* HashTable::getQuery(string key)
{
	LinkedList* Result = new LinkedList();
	unsigned long int hashValue = FNV_1aHash(key);
	if (hashTableArray[hashValue] != NULL) {
		ListItem* current = hashTableArray[hashValue]->head;
		while (current != NULL) {
			Result->insertItem(current->data);
			current = current->next;
		}
	}
	else
		return NULL;
	Result->transfered = 1;
	return Result;
}

void HashTable::displayAllRecords()
{
	for (int i = 0; i < this->size; i++)
	{
		if (hashTableArray[i] != NULL) {
			cout <<endl<< "Hash Table Value of " << i < , endl;
			hashTableArray[i]->displayList();
		}
	}
}
