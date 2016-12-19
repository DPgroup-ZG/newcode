#ifndef PROXY_H_
#define PROXY_H_
//	代理模式
class DIALOG1;
class IMemMalloc
{
public:
	IMemMalloc(DIALOG1* dg, int wn, int sz)
	{
		dlg1 = dg;
		workNo = wn;
		size = sz;

	}
	virtual ~IMemMalloc() {}
	virtual void AllocateMemory() {}
protected:
	int workNo; 
	int size;
	DIALOG1* dlg1;
};


class RealMalloc : public IMemMalloc
{
public:
	RealMalloc(DIALOG1* dg, int wn, int sz) :IMemMalloc(dg, wn, sz) {}
	~RealMalloc() {}
	void AllocateMemory() 
	{ 
		dlg1->AllocateMemory(workNo, size);
	}
};


class RealMallocProxy : public IMemMalloc
{
private:
	RealMalloc *m_malloc;
public:
	RealMallocProxy(DIALOG1* dg, int wn, int sz) :IMemMalloc(dg, wn, sz), m_malloc(0) {}
	~RealMallocProxy() { delete m_malloc; }
	void AllocateMemory()
	{
		if (m_malloc == NULL)
			m_malloc = new RealMalloc(dlg1, workNo, size);
		m_malloc->AllocateMemory();
	}
};
#endif