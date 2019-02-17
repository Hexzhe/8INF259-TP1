#pragma once
#include "pch.h"
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	Tail = Head = Current = new LinkedListNode<T>;
}

template <class T>
void LinkedList<T>::Clear()
{
	while (Head->Next != nullptr)
	{
		Current = Head->Next; //We don't delete head
		Head->Next = Current->Next;
		delete Current;
	}
	
	Current = Tail = Head;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Clear();
	delete Head;
}

template <class T>
void LinkedList<T>::Insert(const T & item)
{
	assert(Current != nullptr); //Abort if we aren't in the list

	Current->Next = new LinkedListNode<T>(item, Current->Next);

	if (Tail == Current) //If current was tail, tail is now the new item
		Tail = Current->Next;
}

template <class T>
bool LinkedList<T>::IsInRange() const
{
	return (Current != nullptr) && (Current->Next != nullptr); 
}

template <class T>
T LinkedList<T>::Remove()
{
	assert(IsInRange());

	T tmp = Current->Next->Item;
	LinkedListNode<T> * pTmp = Current->Next;
	Current->Next = pTmp->Next;

	if (Tail == pTmp)
		Tail = Current;

	delete pTmp;
	return tmp;
}

template <class T>
void LinkedList<T>::Add(const T & item)
{
	Tail = Tail->Next = new LinkedListNode<T>(item, nullptr);
}

template <class T>
void LinkedList<T>::MovePrevious()
{
	if ((Current == nullptr) || (Current == Head))
	{
		Current = nullptr;
		return;
	}

	LinkedListNode<T> * tmp = Head;
	while ((tmp != nullptr) && (tmp->Next != Current))
		tmp = tmp->Next;

	Current = tmp;
}

template <class T>
void LinkedList<T>::MoveNext()
{
	if (Current != nullptr)
		Current = Current->Next;
}

template <class T>
int LinkedList<T>::Count() const
{
	int count = 0;
	for (LinkedListNode<T> * tmp = Head->Next; tmp != nullptr; tmp = tmp->Next)
		count++;

	return count;
}

template <class T>
void LinkedList<T>::Move(const int pos)
{
	Current = Head;
	for (int i = 0; (Current != nullptr) && (i < pos); i++)
		Current = Current->Next;
}

template <class T>
void LinkedList<T>::SetValue(const T & value)
{
	assert(IsInRange());
	Current->Next->Item = value;
}

template <class T>
T LinkedList<T>::GetValue()
{
	assert(IsInRange());
	return Current->Next->Item;
}

template <class T>
int LinkedList<T>::Find(const T & value)
{
	Move(0);

	for (int i = 0; IsInRange(); i++)
	{
		if (Current->Next->Item == value)
			return i;
		else
			MoveNext();
	}

	Move(0);

	return -1;
}