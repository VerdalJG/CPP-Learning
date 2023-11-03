#include "TList.h"
#include <iostream>

TListNode::TListNode(const char* _string)
	: m_pString(_string)
{
	//printf("Node Default Constructor\n");
}

TListNode::TListNode(const TListNode& _tListNode)
{
	m_pNext = nullptr;
	m_pString = nullptr;

	if (_tListNode.m_pString)
	{
		m_pString = new char[strlen(_tListNode.m_pString) + 1];
		strcpy(const_cast<char*>(m_pString), _tListNode.m_pString);
	}
	else
	{
		m_pString = nullptr;
	}

	//printf("Node Copy Constructor\n");
}


TListNode::~TListNode()
{

}


TList::TList()
	: m_uSize(0)
	, m_pFirst(nullptr)
	, m_pCurrent(nullptr)
{
	//printf("TList Default Constructor\n");
}

TList::TList(const TList& _list)
	: m_uSize(_list.m_uSize)
	, m_pFirst(nullptr)
	, m_pCurrent(nullptr)
{
	if (_list.m_pFirst)
	{
		m_pFirst = new TListNode(_list.m_pFirst->m_pString);
		TListNode* currentNode = m_pFirst;
		TListNode* sourceNode = _list.m_pFirst->m_pNext;

		while (sourceNode) 
		{
			// Create a new node and copy the contents of the source node
			currentNode->m_pNext = new TListNode(*(sourceNode));
			currentNode = currentNode->m_pNext;
			sourceNode = sourceNode->m_pNext;
		}
	}
	else
	{
		m_pFirst = nullptr;
	}
	m_pCurrent = m_pFirst;

	printf("TList Copy Constructor\n");
}

unsigned int TList::Size()
{
	return m_uSize;
}

int TList::Push(const char* _sToPush)
{
	if (m_pFirst == nullptr)
	{
		m_pFirst = new TListNode(_sToPush);
		m_pCurrent = m_pFirst;
	}
	else
	{
		TListNode* pList = m_pFirst; // pointer to first
		while (pList->m_pNext) // if the first item has a next item
		{
			pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
		}
		pList->m_pNext = new TListNode(_sToPush); // once you have the last item, create a new object and set next to its pointer
	}
	return ++m_uSize;
}

const char* TList::First()
{
	m_pCurrent = m_pFirst;

	// Return the first value if it exists
	if (m_pFirst)
	{
		return m_pFirst->m_pString;
	}

	// Return nullptr if it doesnt
	return nullptr;
}

const char* TList::Next()
{
	if (m_pCurrent != nullptr)
	{
		m_pCurrent = m_pCurrent->m_pNext;
	}
	else
	{
		if (m_pFirst) m_pCurrent = m_pFirst;
	}
	return m_pCurrent ? m_pCurrent->m_pString : nullptr;
}

const char* TList::Pop()
{
	const char* result = nullptr;
	if (m_pFirst)
	{
		TListNode* pTmp = m_pFirst;
		result = m_pFirst->m_pString;
		m_pFirst = m_pFirst->m_pNext;
		delete pTmp;
		--m_uSize;
	}
	return result;
}

void TList::Reset()
{
	while (m_pFirst)
	{
		Pop();
	}
}

void TList::GetReverseList() 
{
	TListNode* previous = nullptr;
	TListNode* current = m_pFirst;
	TListNode* next = nullptr;
	
	while (current != nullptr)
	{
		next = current->m_pNext;
		current->m_pNext = previous;
		previous = current;
		current = next;
	}
	m_pFirst = previous;
}
