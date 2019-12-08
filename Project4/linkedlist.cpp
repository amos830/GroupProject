#include <stdio.h>
#include <iostream>
#include "linkedlist.h"
#include "ListItem.h"

using namespace std;
int LinkedList::sortCount;
void LinkedList::displayCount()
{
	int count = 0;
	ListItem* current = head;
	while (current != NULL)
	{
		current=current->next;
		count++;
	}
	cout << "Number of Records: " << count << endl;
	this->count = count;
}
//Given
LinkedList::LinkedList() {
	LinkedList::head = NULL;
	last = head;
	transfered = 0;
	count = 0;
	hasData = false;
	//cout <<this<< " created" << endl;
}
LinkedList::LinkedList(ListItem* head) {
	this->head = head;
	last = head;
	head->next = NULL;
	transfered = 0;
	count = 1;
}

// Check whether a list is empty
// Given
bool LinkedList::isEmpty() {
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
void LinkedList::insertItem(record* record) {
	//Begin coding here
	if (isEmpty()) {
		head=new ListItem(record);
		last = head;
		count++;
		return;
	}
	ListItem* current=new ListItem(record);
	current->next = head;
	count++;
	head = current;
}

void LinkedList::insertItem(ListItem* node) {
	if (isEmpty()) {
		head = node;
		last = head;
		head->next=NULL;
		return;
	}
	node->next = head;
	head = node;
	count++;
	return;
}

void LinkedList::markDeepDelete()
{
	ListItem* current = head;
	while(current!=NULL){
		current->data->deepDelete = 1;
		current = current->next;
	}
}

// As head is set to public, this is totally an option for you to use
void LinkedList::setHead(ListItem* n) {
	LinkedList::head = n;
}

LinkedList* LinkedList::quicksort()
{
	bool is = isSorted();
	//ListItem* wrong = isNotSorted();
	if(!is)
	//if(wrong)
	{
		LinkedList* smallList=new LinkedList();
		LinkedList* largeList =new LinkedList();
		ListItem* current = head->next;
		LinkedList* pivot=new LinkedList();
		pivot->insertItem(head);
		//ListItem* current = head;
		//pivot->head= wrong;
		//pivot->last = wrong;
		ListItem* temp;
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			if (pivot->head->data->country > temp->data->country)
				smallList->insertItem(temp);
			else if (pivot->head->data->country.compare(temp->data->country)==0)
				pivot->insertItem(temp);
			else 
				largeList->insertItem(temp);
		}
		this->transfered = 1;
		delete this;
		/*cout << "Sort Count "<<++sortCount<< endl;
		cout << "small list address :" <<smallList<< endl;
		smallList->displayList();
		cout << "pivot " << endl;
		pivot->displayList();
		cout << "large address :" << largeList << endl;
		largeList->displayList();
		cout << endl; //DEBUG*/
		if(smallList->count>largeList->count)
			return LinkedList::combineLarge(smallList->quicksort(),largeList->quicksort(), pivot);
		else
			return LinkedList::combine(largeList->quicksort(), smallList->quicksort(),pivot);
	}
	return this;
}

LinkedList* LinkedList::combineLarge(LinkedList* first, LinkedList* second, LinkedList* pivot) {
	/*	cout << "before" << endl;
		cout << "first" << endl;
		first->displayList();
		cout << "before change ";
		first->last->data->displayRecord();
		cout << "pivot" << endl;
		pivot->displayList();
		cout << "second" << endl;
		second->displayList();			 */			//DEBUG		
	if (first->isEmpty()) {
		first->head = pivot->head;
		if (second->isEmpty()) {
			pivot->last->next = NULL;
			first->last = pivot->last;
		}
		else {
			pivot->last->next = second->head;
			first->last = second->last;
		}
	}
	else {
		first->last->next = pivot->head;
		if (second->isEmpty()) {
			pivot->last->next = NULL;
			first->last = pivot->last;
		}
		else {
			pivot->last->next = second->head;
			first->last = second->last;
		}
	}
	second->transfered = 1;
	//second->~LinkedList();
	pivot->transfered = 1;
	delete pivot;
	delete second;
	second = NULL;
	/*cout << "combined" << endl;
	first->displayList();	//DEBUG*/
	return first;
}

LinkedList* LinkedList::combine(LinkedList* second, LinkedList* first,LinkedList* pivot){
/*	cout << "before" << endl;
	cout << "first" << endl;
	first->displayList();
	cout << "before change ";
	first->last->data->displayRecord();
	cout << "pivot" << endl;
	pivot->displayList();
	cout << "second" << endl;
	second->displayList();			 */			//DEBUG		
		if (first->isEmpty()) {
			first->head = pivot->head;
			if (second->isEmpty()) {
				pivot->last->next = NULL;
				first->last = pivot->last;
			}
			else {
				pivot->last->next = second->head;
				first->last = second->last;
			}
		}
		else {
			first->last->next = pivot->head;
			if (second->isEmpty()) {
				pivot->last->next = NULL;
				first->last = pivot->last;
			}
			else {
				pivot->last->next = second->head;
				first->last = second->last;
			}
		}
		second->transfered = 1;
		//second->~LinkedList();
		pivot->transfered = 1;
		delete pivot;
		delete second;
		second = NULL;
		/*cout << "combined" << endl;
		first->displayList();	//DEBUG*/
	return first;
}

void LinkedList::linearsearchRecord(int type, string key)
{
	int countdisplay = 0;
	ListItem* current = head;
	switch (type) {
	case 1:
		cout << endl << "-------------------------------------------------------------" << endl;
		cout << "Search of Phone Number "<<key<<" Yield These Results" << endl;
		cout << endl << "-------------------------------------------------------------" << endl;
		while (current != NULL)
		{
			if (current->data->pNumber.compare(key) == 0) {
				current->data->displayRecord();
				countdisplay++;
			}
			current = current->next;
		}
		break;
	case 2:
		cout << endl << "-------------------------------------------------------------" << endl;
		cout << "Search of Skills " << key << " Yield These Results" << endl;
		cout << endl << "-------------------------------------------------------------" << endl;
		while (current != NULL)
		{
			if (current->data->skills.compare(key) == 0) {
				current->data->displayRecord();
				countdisplay++;
			}
			current = current->next;
		}
		break;
	case 3:
		cout << endl << "-------------------------------------------------------------" << endl;
		cout << "Search of Job Title " << key << " Yield These Results" << endl;
		cout << endl << "-------------------------------------------------------------" << endl;
		while (current != NULL)
		{
			if (current->data->jobTitle.compare(key) == 0) {
				current->data->displayRecord();
				countdisplay++;
			}
			current = current->next;
		}
		break;
	case 4:
		cout << endl << "-------------------------------------------------------------" << endl;
		cout << "Search of Country " << key << " Yield These Results" << endl;
		cout << endl << "-------------------------------------------------------------" << endl;
		while (current != NULL)
		{
			if (current->data->country.compare(key) == 0) {
				current->data->displayRecord();
				countdisplay++;
			}
			current = current->next;
		}
		break;
		}
		if (countdisplay == 0)
			cout << "Record Not Found" << endl;
		else
			cout << "displayed " << countdisplay << " Results" << endl;
}

void LinkedList::displayList()
{
	ListItem* current = head;
	int count = 0;
	while (current != NULL)
	{
		cout << count << ". ";
		current->data->displayRecord();
		current = current->next;
		count++;
	}
	cout << "Displayed "<< count << " items"<<endl;

	//cout << "list displayed sycessfully" << endl;	//DEBUG
}

LinkedList::~LinkedList() {
	if (!this->transfered) {
		emptyList();
	}
	//cout << this << " deleted" << endl;
}

void LinkedList::emptyList()
{
	ListItem* curr = head;
	ListItem* next = NULL;

	while (curr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	cout << this << " content deleted" << endl;
}

bool LinkedList::isSorted()
{
	if (isEmpty()||head->next==NULL) {
		return true;
	}
	ListItem* current = head;
	while (current->next != NULL)
	{
		if(current->data->country > current->next->data->country)
			return false;
		current = current->next;
	}
	return true;
}
ListItem* LinkedList::isNotSorted()
{
	if (isEmpty() || head->next == NULL) {
		return NULL;
	}
	ListItem* current = head;
	while (current->next != NULL)
	{
		if (current->data->country > current->next->data->country)
			return current;
		current = current->next;
	}
	return NULL;
}

