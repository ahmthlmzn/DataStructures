#include "Deque.h"
#include <iostream>
using namespace std;

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	this->head = this->tail = NULL;
	this->noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	while (this->head) {
		DequeNode* node = this->head;
		this->head = this->head->next;
		delete node;
	} //end-while
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode* node = new DequeNode(item);
	
		// If deque is empty 
		if (this->head == NULL)
			this->tail = this->head = node;

		// Inserts node at the front end 
		else
		{
			node->next = this->head;
			this->head->prev = node;
			this->head = node;
		}
		// Increments count of elements by 1 
		this->noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode* node = new DequeNode(item);
	// If true then new element cannot be added 
	// and it is an 'Overflow' condition 
		// If deque is empty 
		if (this->tail == NULL)
			this->head = this->tail = node;

		// Inserts node at the rear end 
		else
		{
			node->prev = this->tail;
			this->tail->next = node;
			this->tail = node;
		}
		this->noOfItems++;
	
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (this->head == NULL) throw std::exception("Deque::RemoveFront(): Empty queue");

	int item = this->head->item;//3 5 7
	DequeNode* node = this->head;
	this->head = this->head->next;

	// If only one element was present 
	if (this->head == NULL)
		this->tail = NULL;
	else
		this->head->prev = NULL;
	delete node;

	// Decrements count of elements by 1 
	this->noOfItems--;
	return item;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (this->head == NULL) throw std::exception("Deque::RemoveRear(): Empty queue");

	int item = this->tail->item;
	DequeNode* node = this->tail;
	this->tail = this->tail->prev;

	// If only one element was present 
	if (this->tail == NULL)
		this->head = NULL;
	else
		this->tail->next = NULL;
	delete node;

	// Decrements count of elements by 1 
	this->noOfItems--;
	return item;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (this->head == NULL) throw std::exception("Deque::Front(): Empty queue");
	return this->head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (this->tail == NULL) throw std::exception("Deque::Rear(): Empty queue");
	return this->tail->item;
} //end-Rear
