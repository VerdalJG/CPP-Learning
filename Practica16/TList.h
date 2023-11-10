#pragma once

class IData
{
public:
	virtual void Print() = 0;
	virtual IData* Clone() const = 0;
};

class TListNode
{
public:
	// Constructors
	TListNode(const IData* _pData);
	TListNode(const TListNode& _tListNode);
	~TListNode();


	// To do: Variables... make them private?
	TListNode* m_pNext = nullptr;
	const IData* m_pData;
};


class TList
{
public:
	TList();

	TList(const TList& _list);

	//TList GetReverseList(TList _list);

	unsigned int Size(); // Returns the number of elements in the list

	int Push(const IData* sToPush); // Adds an element to the list, placing it first

	const IData* First(); // Returns the first element from the list

	const IData* Next(); // Returns the next element from the list

	const IData* Pop(); // Eliminates 1st element from the list and returns it

	void Reset(); // Eliminate all list elements

	void GetReverseList(); // Returns a new list with reversed elements



private:
	int m_uSize;
	TListNode* m_pFirst;
	TListNode* m_pCurrent;
};

