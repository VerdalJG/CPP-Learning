#pragma once

template<typename T>
class TListNode
{
public:
	// Constructors
	TListNode(T* _item);
	TListNode(T _item);
	TListNode(const TListNode& _tListNode);
	~TListNode();


	// To do: Variables... make them private?
	TListNode* m_pNext = nullptr;
	T* m_pItem = nullptr;
};

template<typename T>
class List
{
public:
	List();

	List(const List& _list);

	unsigned int Size(); // Returns the number of elements in the list

	int Push(T* item); // Adds an element to the list, placing it first

	int Push(T item); // Adds an element to the list, placing it first

	T* First(); // Returns the first element from the list

	T* Next(); // Returns the next element from the list

	T* Pop(); // Eliminates 1st element from the list and returns it

	void Reset(); // Eliminate all list elements

	void GetReverseList(); // Returns a new list with reversed elements



private:
	int m_uSize;
	TListNode<T>* m_pFirst;
	TListNode<T>* m_pCurrent;
};

