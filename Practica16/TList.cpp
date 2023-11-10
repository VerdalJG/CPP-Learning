#include "TList.h"
#include <iostream>

TListNode::TListNode(const IData* _pData)
	: m_pData(_pData)
{
	//printf("Node Default Constructor\n");
}

TListNode::TListNode(const TListNode& _tListNode)
{
	m_pNext = nullptr;
	m_pData = nullptr;

	if (_tListNode.m_pData)
	{
		m_pData = new IData();
	}
	else
	{
		m_pData = nullptr;
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
		m_pFirst = new TListNode(_list.m_pFirst->m_pData);
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

int TList::Push(const IData* _dataToPush)
{
	if (m_pFirst == nullptr)
	{
		m_pFirst = new TListNode(_dataToPush);
		m_pCurrent = m_pFirst;
	}
	else
	{
		TListNode* pList = m_pFirst; // pointer to first
		while (pList->m_pNext) // if the first item has a next item
		{
			pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
		}
		pList->m_pNext = new TListNode(_dataToPush); // once you have the last item, create a new object and set next to its pointer
	}
	return ++m_uSize;
}

const IData* TList::First()
{
	m_pCurrent = m_pFirst;

	// Return the first value if it exists
	if (m_pFirst)
	{
		return m_pFirst->m_pData;
	}

	// Return nullptr if it doesnt
	return nullptr;
}

const IData* TList::Next()
{
	if (m_pCurrent != nullptr)
	{
		m_pCurrent = m_pCurrent->m_pNext;
	}
	else
	{
		if (m_pFirst) m_pCurrent = m_pFirst;
	}
	return m_pCurrent ? m_pCurrent->m_pData : nullptr;
}

const IData* TList::Pop()
{
	const IData* result = nullptr;
	if (m_pFirst)
	{
		TListNode* pTmp = m_pFirst;
		result = m_pFirst->m_pData;
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
