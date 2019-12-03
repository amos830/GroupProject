#pragma once
#include "record.h"
#include <map>
#define _CRTDBG_MAP_ALLOC
class ItemNode {
public:
	shared_ptr<record> data;
	ItemNode* next;
	ItemNode(record* data);
	//ItemNode(record* data);
	//ItemNode(record data);
	~ItemNode();
	// This is a constructor done for you.  You should be able to finish the test with this constructor
};
class InventoryList
{

public:
	// Head pointer
	ItemNode* head;
	int transfered;
	InventoryList();
	InventoryList(ItemNode* head);
	~InventoryList();
	void emptyList();
	bool isSorted();
	//Return true if the list is empty
	bool isEmpty();
	int count;
	int id;
	//Append an item to the linked list.  The new item will be the last item in the list
	//void insertItem(record* record);
	void insertItem(record* record);
	void insertItem(ItemNode* node);
	void markDeepDelete();
	//Remove the item with the specified item code
	// Setting the head pointer point to the first element
	void setHead(ItemNode* node);
	static int sortCount;
	// Getting the head pointer of the inventory list
	//shared_ptr<ItemNode> getHead();
	InventoryList* quicksort();
	void combine(InventoryList* target);
	static InventoryList* combine(InventoryList* first, InventoryList* second);
	//shared_ptr<InventoryList> combine(shared_ptr<InventoryList> first, shared_ptr<InventoryList> second, shared_ptr<ItemNode> pivot);
	InventoryList* combine(InventoryList* first, InventoryList* second, ItemNode* pivot);
	//InventoryList* combine(InventoryList* first, InventoryList* second, shared_ptr<ItemNode> pivot);
	void displayList();
	bool hasData;
};