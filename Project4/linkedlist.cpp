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
}
InventoryList::InventoryList(ItemNode* head) {
	head = head;
	transfered = 0;
	count = 1;
}

// Check whether a list is empty
// Given
bool InventoryList::isEmpty() {
	return InventoryList::head == NULL ? true : false;
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
ItemNode* InventoryList::getHead() {
	return head;
}

InventoryList* InventoryList::quicksort()
{
	shared_ptr<InventoryList> smallList(new InventoryList());
	shared_ptr<InventoryList> largeList(new InventoryList());
	bool is = this->isSorted();
	bool is2 = string("Ar") < string("Br");
	if(!is)
	{
		ItemNode* current = head->next;
		shared_ptr<ItemNode>pivot(head);
		while (current != NULL)
		{
			if (pivot->data->country >= current->data->country) 
				smallList->insertItem(current->data.get());
			else 
				largeList->insertItem(current->data.get());
			ItemNode* tem = current;
			current = current->next;
			tem->data->deepDelete = 0;
			delete tem;
		}
		/*cout << "Sort Count "<<++sortCount<< endl;
		cout << "small list address :" <<smallList<< endl;
		smallList->displayList();
		cout << "pivot "<<pivot->data.country<< endl;
		cout << "large address :" << largeList << endl;
		largeList->displayList();
		cout << endl;*/
		InventoryList* sortedS = smallList->quicksort();
		InventoryList* sortedL=largeList->quicksort();
		InventoryList* output=InventoryList::combine(sortedS, sortedL,pivot);
		//sortedS->emptyList(true);
		return output;
	}
	return this;
}

void InventoryList::combine(InventoryList* target)
{
	if(!(target->isEmpty()))
		if (isEmpty())
			head = target->head;
		else {
			ItemNode* current = head;
			while (current->next!= NULL)
				current = current->next;
			current->next = target->head;
		}
	target->transfered = 1;
}
InventoryList* InventoryList::combine(InventoryList* first,InventoryList* second)
{
	if (!(second->isEmpty())) {
		if (first->isEmpty())
			first->head = second->head;
		else {
			ItemNode* current = first->head;
			while (current->next != NULL&&current!=NULL)
				current = current->next;
			current->next = second->head;
		}
		second->transfered = 1;
		//delete second;
	}
	return first;
}
InventoryList* InventoryList::combine(InventoryList* first, InventoryList* second,shared_ptr<ItemNode> pivot)
{
	/*cout << "before" << endl;
	cout << "first" << endl;
	first->displayList();
	cout << "pivot: " << pivot->data.country<<endl;
	cout << "second" << endl;
	second->displayList();*/
		if (first->isEmpty())
			first->head = second->head;
		else {
			ItemNode* current = first->head;
			while (current->next != NULL)
				current = current->next;
				current->next = pivot.get();
				pivot->next=second->head;
		}
		second->transfered = 1;
		second->~InventoryList();
	//cout << "combined" << endl;
	//first->displayList();
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