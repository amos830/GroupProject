#pragma once
#include "record.h"

class ListItem {
public:
	record* data;
	ListItem* next;
	ListItem(record* data);
	//ListItem(record* data);
	//ListItem(record data);
	~ListItem();
	// This is a constructor done for you.  You should be able to finish the test with this constructor
};

