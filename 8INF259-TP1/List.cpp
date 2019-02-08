#include "pch.h"
#include "List.h"
#include "Node.h"
#include <cassert>

template <class T>
List<T>::List()
{
	Tail = Head = Current = new Node<T>;
}

template <class T>
void List<T>::Clear()
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
List<T>::~List()
{
	Clear();
	delete Head;
}

template <class T>
void List<T>::Insert(const T & item)
{
	assert(Current != nullptr); //Abort if we aren't in the list

	Current->Next = new Node<T>(item, Current->Next);

	if (Tail == Current) //If current was tail, tail is now the new item
		Tail = Current->Next;
}

template <class T>
bool List<T>::IsInRange() const
{
	return (Current != nullptr) && (Current->Next != nullptr); 
}

template <class T>
T List<T>::Remove()
{
	assert(IsInRange());

	T tmp = Current->Next->Item;
	Node<T> * pTmp = Current->Next;
	Current->Next = pTmp->Next;

	if (Tail == pTmp)
		Tail = Current;

	delete pTmp;
	return tmp;
}

template <class T>
void List<T>::Add(const T & item)
{
	Tail = Tail->Next = new Node<T>(item, nullptr);
}

template <class T>
void List<T>::MovePrevious()
{
	if ((Current == nullptr) || (Current == Head))
	{
		Current = nullptr;
		return;
	}

	Node<T> * tmp = Head;
	while ((tmp != nullptr) && (tmp->Next != Current))
		tmp = tmp->Next;

	Current = tmp;
}

template <class T>
void List<T>::MoveNext()
{
	if (Current != nullptr)
		Current = Current->Next;
}

template <class T>
int List<T>::Count() const
{
	int count = 0;
	for (Node<T> * tmp = Head->Next; tmp != nullptr; tmp = tmp->Next)
		count++;

	return count;
}

template <class T>
void List<T>::Move(const int pos)
{
	Current = Head;
	for (int i = 0; (Current != nullptr) && (i < pos); i++)
		Current = Current->Next;
}

template <class T>
void List<T>::SetValue(const T & value)
{
	assert(IsInRange());
	Current->Next->Item = value;
}

template <class T>
T List<T>::GetValue() const
{
	assert(IsInRange());
	return Current->Next->Item;
}

template <class T>
int List<T>::Find(const T & value)
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