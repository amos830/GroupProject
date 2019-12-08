#include "linkedlist.h"
#include "ListItem.h"
#include <cmath>
#pragma once
class HashTable {
public:
	HashTable(int size);
	~HashTable();
	unsigned long int FNV_1aHash(string key);
	unsigned long int lastKey;
	int size;
	LinkedList** hashTableArray;
	void insertRecord(string key, record* value);
	LinkedList* getQuery(string key);
	int bitRequired;
	void displayAllRecords();
	void
};