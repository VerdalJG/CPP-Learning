#pragma once

class TListNode
{
public:
	// Constructors
	TListNode(const char* _string);
	TListNode(TListNode& _tListNode);
	~TListNode();


	// To do: Variables... make them private?
	TListNode* m_pNext = nullptr;
	const char* m_pString = nullptr;
};


class TList
{
public:
	TList();

	TList(TList& _CList);

	//TList GetReverseList(TList _list);

	unsigned int Size(); // Returns the number of elements in the list

	int Push(const char* sToPush); // Adds an element to the list, placing it first

	const char* First(); // Returns the first element from the list

	const char* Next(); // Returns the next element from the list

	const char* Pop(); // Eliminates 1st element from the list and returns it

	void Reset(); // Eliminate all list elements



private:
	int m_uSize;
	TListNode* m_pFirst;
	TListNode* m_pCurrent;
};

