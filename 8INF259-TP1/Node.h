#pragma once

template <class T>
class Node
{
public:
	T Item;
	Node* Next;
	Node(Node* next = nullptr)
	{
		Next = next;
	}
	Node(const T& item, Node* next = nullptr)
	{
		Item = item;
		Next = next;
	}
	~Node() {}
};

