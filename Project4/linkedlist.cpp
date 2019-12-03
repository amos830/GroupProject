#include <stdio.h>
#include <iostream>
#include "linkedlist.h"

using namespace std;
int InventoryList::sortCount;
//Given
InventoryList::InventoryList() {
	InventoryList::head = NULL;
	transfered = 0;
	count = 0;
	hasData = false;
	//cout <<this<< " created" << endl;
}
InventoryList::InventoryList(ItemNode* head) {
	head = head;
	transfered = 0;
	count = 1;
}

// Check whether a list is empty
// Given
bool InventoryList::isEmpty() {
	return head == NULL ? true : false;
}

/*
 Tasks 2: Printing the inventory list on screen

 The function should be able to display item details stored in the linked list structure on screen.
 The actual format of printing, please refer to the problem description

 After this task, item data in the linked list should be displayed on screen.
 */

/*
 Tasks 3: Insert an item to the list

 The function will append a new item to the end of the linked list.  Display either successful
 or fail message according to the insertion result.
 */
void InventoryList::insertItem(record* record) {
	//Begin coding here
	if (isEmpty()) {
		head=new ItemNode(record);
		count++;
		return;
	}
	ItemNode* current=new ItemNode(record);
	current->next = head;
	count++;
	head = current;
}
void InventoryList::insertItem(ItemNode* node) {
	if (isEmpty()) {
		head = node;
		head->next=NULL;
		return;
	}
	node->next = head;
	head = node;
	count++;
	return;
}

void InventoryList::markDeepDelete()
{
	ItemNode* current = head;
	while(current!=NULL){
		current->data->deepDelete = 1;
		current = current->next;
	}
}

/*
 Tasks 6: Forming a linked list with only priority item

 The function will perform the following tasks:
 1) Create an inventory list, say, tempList for the priority item(s)
 2) Look for all priority items in the original linked list.
 3) If any priority item found, append the priority item to the tempList
 4) Return the tempList

 After this task, a head pointer (ItemNode*) to priority item list is returned.
 */

// As head is set to public, this is totally an option for you to use
void InventoryList::setHead(ItemNode* n) {
	InventoryList::head = n;
}

// As head is set to public, this is totally an option for you to use
/*ItemNode* InventoryList::getHead() {
	return head;
}*/

InventoryList* InventoryList::quicksort()
{
	bool is = isSorted();
	if(!is)
	{
		InventoryList* smallList=new InventoryList();
		InventoryList* largeList =new InventoryList();
		ItemNode* current = head->next;
		ItemNode* pivot =head;
		ItemNode* temp;
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			if (pivot->data->country >= temp->data->country) {
				smallList->insertItem(temp);
			}
			else {
				largeList->insertItem(temp);
			}
		}
		this->transfered = 1;
		delete this;
		/*cout << "Sort Count "<<++sortCount<< endl;
		cout << "small list address :" <<smallList<< endl;
		smallList->displayList();
		cout << "pivot "<<pivot->data->country<< endl;
		cout << "large address :" << largeList << endl;
		largeList->displayList();
		cout << endl;*/  //DEBUG
		return InventoryList::combine(largeList->quicksort(), smallList->quicksort(),pivot);
	}
	return this;
}
InventoryList* InventoryList::combine(InventoryList* second, InventoryList* first,ItemNode* pivot){
	/*cout << "before" << endl;
	cout << "first" << endl;
	first->displayList();
	cout << "second" << endl;
	cout << pivot->data->country << endl;
	second->displayList();*/ //DEBUG
		if (first->isEmpty()) {
			first->head = pivot;
			if (second->isEmpty())
				pivot->next = NULL;
			else
				pivot->next = second->head;
		}
		else {
			ItemNode* current = first->head;
			while (current->next != NULL)
				current = current->next;
			current->next = pivot;
			if (second->isEmpty())
				pivot->next = NULL;
			else
				pivot->next = second->head;
		}
		second->transfered = 1;
		//second->~InventoryList();
		delete second;
		second = NULL;
		/*cout << "combined" << endl;
		first->displayList();*/	//DEBUG
	return first;
}
void InventoryList::displayList()
{
	ItemNode* current = head;
	int count = 0;
	while (current != NULL)
	{
		cout<<++count<<". "
		<<current->data->ID<<" "
		<<current->data->jobTitle << " " 
		<<current->data->emailAddress << " " 
		<<current->data->lastName << " " 
		<<current->data->firstName << " " 
		<<current->data->pNumber << " " 
		<<current->data->skills << " " 
		<<current->data->country<<endl<<endl;
			/*<< current->data.ID << " "
			<< current->data.jobTitle << " "
			<< current->data.emailAddress << " "
			<< current->data.lastName << " "
			<< current->data.firstName << " "
			<< current->data.pNumber << " "
			<< current->data.skills << " "
			<< current->data.country << endl << endl;*/
		current = current->next;
	}
	//cout << "list displayed sycessfully" << endl;	//DEBUG
}

InventoryList::~InventoryList() {
	if (!this->transfered) {
		emptyList();
	}
	//cout << this << " deleted" << endl;
}

void InventoryList::emptyList()
{
	ItemNode* curr = head;
	ItemNode* next = NULL;

	while (curr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	cout << this << " content deleted" << endl;
}

bool InventoryList::isSorted()
{
	bool test = 1;
	if (isEmpty()) {
		return true;
	}
	ItemNode* current = head;
	while (current->next != NULL &&test)
	{
		if(current->data->country > current->next->data->country)
			return false;
		current = current->next;
	}
	return true;
}

/*ItemNode::ItemNode(record data)
{
	this->data = data;
	cout << "node: " << data->ID << " From " <<data->country << " created" << endl;
}*/
ItemNode::ItemNode(record* data)
{
	this->data=shared_ptr<record>(data);
}
ItemNode::~ItemNode()
{
	//if(data->deepDelete)
//		delete data;
	//cout << "node: " << data.ID << " From " << data.country << "deleted " <<this<< endl;
}