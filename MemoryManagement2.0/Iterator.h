#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Iterator.h"
using namespace std;

//µü´úÆ÷Ä£Ê½
class Iterator
{
public:
	Iterator() {};
	virtual ~Iterator() {};
	virtual int First() = 0;
	virtual void Next() = 0;
	virtual int GetCur() = 0;
	virtual bool IsEnd() = 0;
};

class Aggregate
{
public:
	virtual int Count() = 0;
	virtual void Push(const int& intValue) = 0;
	virtual int Pop(const int nIndex) = 0;
	virtual Iterator* CreateIterator() = 0;
};

class ConcreteIterator : public Iterator
{
public:
	ConcreteIterator(Aggregate* pAggregate) :m_nCurrent(0), Iterator()
	{
		m_Aggregate = pAggregate;
	}
	int First()
	{
		return m_Aggregate->Pop(0);
	}
	void Next()
	{
		m_nCurrent++;
	}
	int GetCur()
	{
		return m_Aggregate->Pop(m_nCurrent);
	}
	bool IsEnd()
	{
		return ((m_nCurrent >= m_Aggregate->Count()) ? true : false);
	}
private:
	Aggregate* m_Aggregate;
	int m_nCurrent;
};

class ConcreteAggregate : public Aggregate
{
public:
	ConcreteAggregate() :m_pIterator(NULL)
	{
		m_vecItems.clear();
	}
	~ConcreteAggregate()
	{
		if (NULL != m_pIterator)
		{
			delete m_pIterator;
			m_pIterator = NULL;
		}
	}
	Iterator* CreateIterator()
	{
		if (NULL == m_pIterator)
		{
			m_pIterator = new ConcreteIterator(this);
		}
		return m_pIterator;
	}
	int Count()
	{
		return m_vecItems.size();
	}
	void Push(const int& intValue)
	{
		m_vecItems.push_back(intValue);
	}
	int Pop(const int nIndex)
	{
		int intRet;
		if (nIndex < Count())
		{
			intRet = m_vecItems[nIndex];
		}
		return intRet;
	}
private:
	vector<int> m_vecItems;
	Iterator* m_pIterator;
};
