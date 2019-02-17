#pragma once
#include "pch.h"

template <class T>
class LinkedListNode
{
public:
	T Item;
	LinkedListNode * Next;
	LinkedListNode(LinkedListNode * next = nullptr)
	{
		Next = next;
	}
	LinkedListNode(const T & item, LinkedListNode * next = nullptr)
	{
		Item = item;
		Next = next;
	}
	~LinkedListNode() {}
};