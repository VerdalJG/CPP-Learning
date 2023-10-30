#include "CList.h"

CListNode::CListNode(const char* _string)
	: m_pString(_string)
{

}


CListNode::~CListNode()
{

}


CList::CList()
{
}

CList::CList(CList& _CList)
{
}

CList CList::GetReverseList(CList _list)
{
	return CList();
}

unsigned int CList::Size()
{
	return m_uSize;
}

int CList::Push(const char* _sToPush)
{
	if (m_pFirst == nullptr)
	{
		m_pFirst = new CListNode(_sToPush);
	}
	else
	{
		CListNode* pList = m_pFirst; // pointer to first
		while (pList->m_pNext) // if the first item has a next item
		{
			pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
		}
		pList->m_pNext = new CListNode(_sToPush); // once you have the last item, create a new object and set next to its pointer
	}
	return ++m_uSize;
}

const char* CList::First()
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

const char* CList::Next()
{
	if (m_pCurrent != nullptr)
	{
		m_pCurrent = m_pCurrent->m_pNext;
	}
	return m_pCurrent ? m_pCurrent->m_pString : nullptr;
}

const char* CList::Pop()
{
	const char* result = nullptr;
	if (m_pFirst)
	{
		CListNode* pTmp = m_pFirst;
		result = m_pFirst->m_pString;
		m_pFirst = m_pFirst->m_pNext;
		delete pTmp;
		--m_uSize;
	}
	return result;
}

void CList::Reset()
{
	while (m_pFirst)
	{
		Pop();
	}
}
