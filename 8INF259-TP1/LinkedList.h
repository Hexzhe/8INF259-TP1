#pragma once
#include "LinkedListNode.h"

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void Add(const T & item); //Add item at the end of the list. Return the new item's index
	void Insert(const T & item); //Insert item after the current position. Return the new item's index
	T Remove(); //Remove item at current position. Return new current
	int Find(const T &); //Find an item in the list. Return found item's index, -1 otherwise
	void Clear(); //Remove every items
	void Move(const int); //Move the current position at a given index
	void MovePrevious(); //Move the current position a step back. Return new current index
	void MoveNext(); //Move the current position a step forward. Return new current index
	void SetValue(const T&); //Set current item's value
	T GetValue() const; //Return current item's value
	int Count() const; //Return items count
	bool IsInRange() const; //Return true if the current position is out of range
private:
	LinkedListNode<T> * Head;
	LinkedListNode<T> * Tail;
	LinkedListNode<T> * Current;
};

