#include <iostream>
#include "List.h"

template <typename T>
TListNode<T>::TListNode(T* _item)
	: m_pItem(_item)
{
	//printf("Node Default Constructor\n");
}

template <typename T>
TListNode<T>::TListNode(T _item)
{
	m_pItem = new T;
	*m_pItem = _item;
}

template <typename T>
TListNode<T>::TListNode(const TListNode& _tListNode)
{
	m_pNext = nullptr;
	m_pItem = nullptr;

	if (_tListNode.m_pItem)
	{
		m_pItem = new T;
		*m_pItem = *(_tListNode.m_pItem);
	}
	else
	{
		m_pItem = nullptr;
	}

	//printf("Node Copy Constructor\n");
}

template <typename T>
TListNode<T>::~TListNode()
{

}

template <typename T>
List<T>::List()
	: m_uSize(0)
	, m_pFirst(nullptr)
	, m_pCurrent(nullptr)
{
	//printf("TList Default Constructor\n");
}

template <typename T>
List<T>::List(const List& _list)
	: m_uSize(_list.m_uSize)
	, m_pFirst(nullptr)
	, m_pCurrent(nullptr)
{
	if (_list.m_pFirst)
	{
		m_pFirst = new TListNode<T>(_list.m_pFirst->m_pItem);
		TListNode<T>* currentNode = m_pFirst;
		TListNode<T>* sourceNode = _list.m_pFirst->m_pNext;

		while (sourceNode)
		{
			// Create a new node and copy the contents of the source node
			currentNode->m_pNext = new TListNode<T>(*(sourceNode));
			currentNode = currentNode->m_pNext;
			sourceNode = sourceNode->m_pNext;
		}
	}
	else
	{
		m_pFirst = nullptr;
	}
	m_pCurrent = m_pFirst;

	printf("List Copy Constructor\n");
}

template <typename T>
unsigned int List<T>::Size()
{
	return m_uSize;
}

template <typename T>
int List<T>::Push(T* _itemToPush)
{
	if (m_pFirst == nullptr)
	{
		m_pFirst = new TListNode<T>(_itemToPush);
		m_pCurrent = m_pFirst;
	}
	else
	{
		TListNode<T>* pList = m_pFirst; // pointer to first
		while (pList->m_pNext) // if the first item has a next item
		{
			pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
		}
		pList->m_pNext = new TListNode<T>(_itemToPush); // once you have the last item, create a new object and set next to its pointer
	}
	return ++m_uSize;
}

template <typename T>
int List<T>::Push(T _itemToPush)
{
	if (m_pFirst == nullptr)
	{
		m_pFirst = new TListNode<T>(_itemToPush);
		m_pCurrent = m_pFirst;
	}
	else
	{
		TListNode<T>* pList = m_pFirst; // pointer to first
		while (pList->m_pNext) // if the first item has a next item
		{
			pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
		}
		pList->m_pNext = new TListNode<T>(_itemToPush); // once you have the last item, create a new object and set next to its pointer
	}
	return ++m_uSize;
}

template <typename T>
T* List<T>::First()
{
	m_pCurrent = m_pFirst;

	// Return the first value if it exists
	if (m_pFirst)
	{
		return m_pFirst->m_pItem;
	}

	// Return nullptr if it doesnt
	return nullptr;
}

template <typename T>
T* List<T>::Next()
{
	if (m_pCurrent != nullptr)
	{
		m_pCurrent = m_pCurrent->m_pNext;
	}
	else
	{
		if (m_pFirst) m_pCurrent = m_pFirst;
	}
	return m_pCurrent ? m_pCurrent->m_pItem : nullptr;
}

template <typename T>
T* List<T>::Pop()
{
	T* result = nullptr;
	if (m_pFirst)
	{
		TListNode<T>* pTmp = m_pFirst;
		result = m_pFirst->m_pItem;
		m_pFirst = m_pFirst->m_pNext;
		delete pTmp;
		--m_uSize;
	}
	return result;
}

template <typename T>
void List<T>::Reset()
{
	while (m_pFirst)
	{
		Pop();
	}
}

template <typename T>
void List<T>::GetReverseList()
{
	TListNode<T>* previous = nullptr;
	TListNode<T>* current = m_pFirst;
	TListNode<T>* next = nullptr;

	while (current != nullptr)
	{
		next = current->m_pNext;
		current->m_pNext = previous;
		previous = current;
		current = next;
	}
	m_pFirst = previous;
}
