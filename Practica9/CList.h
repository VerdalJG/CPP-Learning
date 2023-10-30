#pragma once

class CListNode
{
public:
	// Constructors
	CListNode(const char* _string);
	~CListNode();


	// To do: Variables... make them private?
	CListNode* m_pNext = nullptr;
	const char* m_pString = nullptr;
};


class CList
{
public:
	CList();

	CList(CList& _CList);

	CList GetReverseList(CList _list);

	unsigned int Size(); // Returns the number of elements in the list

	int Push(const char* sToPush); // Adds a string to the list

	const char* First(); // Returns the first element from the list

	const char* Next(); // Returns the next element from the list

	const char* Pop(); // Eliminates 1st element from the list and returns it

	void Reset(); // Eliminate all list elements



private:
	int m_uSize;
	CListNode* m_pFirst;
	CListNode* m_pCurrent;
};

