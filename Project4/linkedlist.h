#pragma once
#include "record.h"
#include "ListItem.h"
#define _CRTDBG_MAP_ALLOC
class LinkedList
{

public:
	// Head pointer
	void displayCount();
	ListItem* head;
	ListItem* last;
	int transfered;
	LinkedList();
	LinkedList(ListItem* head);
	~LinkedList();
	void emptyList();
	bool isSorted();
	ListItem* isNotSorted();
	//Return true if the list is empty
	bool isEmpty();
	int count;
	int id;
	//Append an item to the linked list.  The new item will be the last item in the list
	//void insertItem(record* record);
	void insertItem(record* record);
	void insertItem(ListItem* node);
	void markDeepDelete();
	//Remove the item with the specified item code
	// Setting the head pointer point to the first element
	void setHead(ListItem* node);
	static int sortCount;
	// Getting the head pointer of the inventory list
	//shared_ptr<ListItem> getHead();
	LinkedList* quicksort();
	LinkedList* combineLarge(LinkedList* first, LinkedList* second, LinkedList* pivot);
	LinkedList* combine(LinkedList* second, LinkedList* first, LinkedList* pivot);
	//shared_ptr<LinkedList> combine(shared_ptr<LinkedList> first, shared_ptr<LinkedList> second, shared_ptr<ListItem> pivot);
	LinkedList* combine(LinkedList* first, LinkedList* second, ListItem* pivot);
	void linearsearchRecord(int type, string key);

	//LinkedList* combine(LinkedList* first, LinkedList* second, shared_ptr<ListItem> pivot);
	void displayList();
	bool hasData;
};