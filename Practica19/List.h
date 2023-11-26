#pragma once

template<typename T>
class TListNode
{
public:
	// Constructors
	TListNode(T* _item) : m_pItem(_item) {}
	

	TListNode(T _item)
	{
		m_pItem = new T;
		*m_pItem = _item;
	}

	TListNode(const TListNode& _tListNode)
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


	~TListNode();


	// To do: Variables... make them private?
	TListNode* m_pNext = nullptr;
	T* m_pItem = nullptr;
};

template< class T >
class List
{
public:
	List()
		: m_uSize(0)
		, m_pFirst(nullptr)
		, m_pCurrent(nullptr)
	{

	}

	List(const List& _list)
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

	unsigned int Size() // Returns the number of elements in the list
	{
		return m_uSize;
	}

	int Push(T* item) // Adds an element to the list, placing it first
	{
		if (m_pFirst == nullptr)
		{
			m_pFirst = new TListNode<T>(item);
			m_pCurrent = m_pFirst;
		}
		else
		{
			TListNode<T>* pList = m_pFirst; // pointer to first
			while (pList->m_pNext) // if the first item has a next item
			{
				pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
			}
			pList->m_pNext = new TListNode<T>(item); // once you have the last item, create a new object and set next to its pointer
		}
		return ++m_uSize;
	}

	int Push(T item) // Adds an element to the list, placing it first
	{
		if (m_pFirst == nullptr)
		{
			m_pFirst = new TListNode<T>(item);
			m_pCurrent = m_pFirst;
		}
		else
		{
			TListNode<T>* pList = m_pFirst; // pointer to first
			while (pList->m_pNext) // if the first item has a next item
			{
				pList = pList->m_pNext; // set the pointer to the next, until you reach the last item
			}
			pList->m_pNext = new TListNode<T>(item); // once you have the last item, create a new object and set next to its pointer
		}
		return ++m_uSize;
	}

	T* First() // Returns the first element from the list
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

	T* Next() // Returns the next element from the list
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

	T* Pop() // Eliminates 1st element from the list and returns it
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

	void Reset() // Eliminate all list elements
	{
		while (m_pFirst)
		{
			Pop();
		}
	}

	void GetReverseList() // Returns a new list with reversed elements
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



private:
	int m_uSize;
	TListNode<T>* m_pFirst;
	TListNode<T>* m_pCurrent;
};

