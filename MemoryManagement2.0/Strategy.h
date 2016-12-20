#ifndef STRATEGY_H_
#define STRATEGY_H_
#include "Memory.h"

//	策略模式
//抽象接口
class AllocAlgorithm
{
public:
	virtual void Alloc(Memory* mem, int workNo, int size) = 0;
};

//两种具体的分配算法
class FIRSTFit_Algorithm : public AllocAlgorithm
{
public:
	void Alloc(Memory* mem, int workNo, int size) 
	{ 
		mem->FirstFit(workNo, size);
	}
};

class BESTFit_Algorithm : public AllocAlgorithm
{
public:
	void Alloc(Memory* mem, int workNo, int size)
	{ 
		mem->BestFit(workNo, size);
	}
};

enum AA { FIRSTFIT, BESTFIT }; //标签
class Cache
{
private:
	AllocAlgorithm *m_aa;
public:
	Cache(enum AA aa)
	{
		if (aa == FIRSTFIT)
			m_aa = new FIRSTFit_Algorithm();
		else if (aa == BESTFIT)
			m_aa = new BESTFit_Algorithm();
		else
			m_aa = NULL;
	}
	~Cache() { delete m_aa; }
	void CacheAlloc(Memory* mem, int workNo, int size)
	{ 
		m_aa->Alloc(mem, workNo, size);
	}
};

#endif