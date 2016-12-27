# 软件架构与设计模式课程项目--MemoryManagement(内存管理系统)

>张鸿羽 1452769 （组长）  
郭梦晗 1452810

## 项目简介
**动态分区分配方式**  
假设初始状态下，可用内存空间为640K，输入一作业请求序列，分别用首次适应算法和最佳适应算法进行内存块的分配和回收，并显示出每次分配和回收后的空闲分区链的情况。    
**请求调页分配方式**  
假设每个页面可存放10条指令，分配给一个作业的内存块为4。模拟一个作业的执行过程，该作业有320条指令，即它的地址空间为32页，目前所有页还没有调入内存。
分别用OPT算法、LRU算法和FIFO算法完成调页。

## 设计模式  
本项目重构时用到的设计模式有6个，分别是单例模式、工厂模式、策略模式、状态模式、代理模式、迭代器模式。  

在这个项目开题答辩时，由于理解上的偏差，我们的几个模式使用了MFC框架自带的模式，老师当场指出了我们的问题我们也迅速意识到此项目重在理解并学会自己运用设计模式而不是使用别人写好的模式，于是我们立即改变了项目的实施思路与想法，重新审视了自己的项目并深入理解了所学设计模式，最终选取了几个可以与项目结合的设计模式并**抛开框架完全靠自己实现了每个模式**。自己动手实现也使得我们对设计模式有了更深层次的理解，同时在实践中我们也领略到了设计模式所带来的好处，也为以后更好地去完成其他的项目打下了一定基础。


### 1. 单例模式
  
![单例](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E5%8D%95%E4%BE%8B.png)  
运用在CMemoryManagement20Dlg类
（功能选择对话框）中CMemoryManagement20Dlg类自己通过GetInstance()创建自己的唯一实例，CMemoryManagement20APP通过InitInstance()调用CMemoryManagement20Dlg类中的GetInstance()来创建唯一实例。
减少内存的开销，尤其是频繁的创建和销毁对话框实例，避免对资源的多重占用。
 

##### 主要代码：  
_MemoryManagement2.0Dlg.h_

	class CMemoryManagement20Dlg : public CDialogEx
	{
	public:
		static CMemoryManagement20Dlg* GetInstance();
		...
	private:
		CMemoryManagement20Dlg(CWnd* pParent = NULL);	
		static CMemoryManagement20Dlg *singleton;

	protected:
	...
	};

_MemoryManagement2.0Dlg.cpp_  

	CMemoryManagement20Dlg* CMemoryManagement20Dlg::singleton = NULL;
	...
	...
	CMemoryManagement20Dlg* CMemoryManagement20Dlg::GetInstance()
	{
		if (singleton == NULL)
			singleton = new CMemoryManagement20Dlg();
		return singleton;
	}

_MemoryManagement2.0.cpp_

	...
	//将dlg对话框设为主对话框（最先跳出来的对话框）
	CMemoryManagement20Dlg *dlg = CMemoryManagement20Dlg::GetInstance();
	m_pMainWnd = dlg;
	INT_PTR nResponse = dlg->DoModal();
	...

### 2. 工厂模式
![工厂](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E5%B7%A5%E5%8E%82.png)  
运用于DIALOG1和DIALOG2的创建。首先创建一个接口类SingleCore，SingleCoreA和SingleCoreB作为SingleCore的子类来实现该接口，Factory为工厂，生成基于给定信息的实体类的对象。  
CMemoryManagement20Dlg类使用了该工厂，OnBnClickedButton1()为第一个按钮，获取SingleCoreA的对象并调用它的Show()方法，同理OnBnClickedButton2()获取SingleCoreB的对象并调用它的Show()方法。  
若需增加产品只需扩展工厂类，扩展性更强；使用一个接口调用者只需关心接口，具体实现被屏蔽；将创建过程延迟到子类进行，子类决定实例化哪个工厂类。  
同时这里还用到了单例模式。每一个SingleCore只创建自己的单个对象，即唯一的DIALOG。

##### 主要代码：  
_SingleFactory.h_

	enumCTYPE { DIALOG_1, DIALOG_2 };
	classSingleCore
	{
	public:
		virtualvoid Show() = 0;
	};


	classSingleCoreA : publicSingleCore
	{
	public:
		void Show() 
		{
			DIALOG1 dlg1;
			dlg1.DoModal();
		}
	};

	classSingleCoreB : publicSingleCore
	{
	public:
		void Show() 
		{
			DIALOG2 dlg2;
			dlg2.DoModal();
		}
	};

	classFactory
	{
	public:
		SingleCore* CreateSingleCore(enumCTYPEctype)
		{
			if (ctype == DIALOG_1) //工厂内部判断  
				returnnewSingleCoreA();   
			elseif (ctype == DIALOG_2)
				returnnewSingleCoreB();
			else
				returnNULL;
		}
	};

_MemoryManagement2.0Dlg.h_

	classCMemoryManagement20Dlg : publicCDialogEx
	{
	public:
		afx_msgvoid OnBnClickedButton1();
		afx_msgvoid OnBnClickedButton2();
	     ...
	private:
	...
	protected:
	...
	};


_MemoryManagement2.0Dlg.cpp_

	...
	voidCMemoryManagement20Dlg::OnBnClickedButton1()
	{
		Factory factory;
		SingleCore* single = factory.CreateSingleCore(DIALOG_1);
		single->Show();
	}

	voidCMemoryManagement20Dlg::OnBnClickedButton2()
	{
		Factory factory;
		SingleCore* single = factory.CreateSingleCore(DIALOG_2);
		single->Show();
	}


### 3. 状态模式  
![状态](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E7%8A%B6%E6%80%81.png)  
运用于DIALOG2（请求调页存储管理方式）类，在OnBnClickedButton2()（点击选择置换算法）中实例化RealRun类，该RealRun实例又实例化一个LRUState类或OPTState或类FIFOState类，在这个类的实例里具体进行置换。  

封装了转换规则。将所有与某个状态有关的行为放到一个类中，并且可以方便地增加新的状态，只需要改变对象状态即可改变对象的行为。允许状态转换逻辑与状态对象合成一体，而不是某一个巨大的条件语句块。


##### 主要代码： 
_State.h_

	class RealRun;
	class DIALOG2;

	class State
	{
	public:
		virtual void OPT() {}
		virtual void LRU() {}
		virtual void FIFO() {}
		virtual void CurrentState(RealRun *war) {}
	};


	class RealRun
	{
	private:
		State *m_state;  
		friend class OPTState;
		friend class LRUState;
		friend class FIFOState;
		DIALOG2 *dlg2;
	public:
		RealRun(State *state, DIALOG2* dlg) : m_state(state), dlg2(dlg) {}
		~RealRun() { delete m_state; }
		void SetState(State *state) { delete m_state; m_state = state; }
		void GetState() { m_state->CurrentState(this); }
	};

	class OPTState : public State
	{
	public:
		void OPT(RealRun *war) 
		{
			war->dlg2->OPT();
		}
		void CurrentState(RealRun *war) { OPT(war); }
	};

	class LRUState : public State
	{
	public:
		void LRU(RealRun *war) 
		{
			war->dlg2->LRU();
		}
		void CurrentState(RealRun *war) { LRU(war); }
	};

	class FIFOState : public State
	{
	public:
		void FIFO(RealRun *war) 
		{
			war->dlg2->FIFO();
		}
		void CurrentState(RealRun *war) { FIFO(war); }
	};
	
_DIALOG2.cpp_

	...
	void DIALOG2::OnBnClickedButton2()
	{
		RealRun *relr;
		switch (select_algorithm)
		{
		case 0:
			init();
			display2 = display2 + "最佳置换算法OPT:\r\n";
			relr = new RealRun(new OPTState(), this);
			relr->GetState();
			delete relr;
			break;
		case 1:
			init();
			display2 = display2 + "最近最久未使用置换算法LRU:\r\n";
			relr = new RealRun(new LRUState(), this);
			relr->GetState();
			delete relr;
			break;
		case 2:
			init();
			display2 = display2 + "先进先出置换算法FIFO:\r\n";
			relr = new RealRun(new FIFOState(), this);
			relr->GetState();
			delete relr;
			break;

		default:;
		}
	}
	...
### 4. 代理模式  
![代理](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E4%BB%A3%E7%90%86.png)  
在分配内存空间时使用代理模式。  
首先创建IMemMalloc作为接口，RealMalloc为真实角色，RealMallocProxy为RealMalloc的代理，用该代理类来代表真实角色的功能。
当DIALOG1发出请求时，使用RealMallocProxy来获取RealMalloc类的对象。  
代理对象起到了中介的作用，同时避免直接访问真实对象，保护了目标对象；另外真实角色只用于其实际职责，其他事务由代理角色完成，使得职责更加简洁清晰。

_Proxy.h_

	classDIALOG1;
	classIMemMalloc
	{
	public:
		IMemMalloc(DIALOG1* dg, intwn, intsz)
		{
			dlg1 = dg;
			workNo = wn;
			size = sz;

		}
		virtual ~IMemMalloc() {}
		virtualvoid AllocateMemory() {}
	protected:
		int workNo; 
		int size;
		DIALOG1* dlg1;
	};

	classRealMalloc : publicIMemMalloc
	{
	public:
		RealMalloc(DIALOG1* dg, intwn, intsz) :IMemMalloc(dg, wn, sz) {}
		~RealMalloc() {}
		void AllocateMemory() 
		{ 
			dlg1->AllocateMemory(workNo, size);
		}
	};

	classRealMallocProxy : publicIMemMalloc
	{
	private:
		RealMalloc *m_malloc;
	public:
		RealMallocProxy(DIALOG1* dg, intwn, intsz) :IMemMalloc(dg, wn, sz), m_malloc(0) {}
		~RealMallocProxy() { delete m_malloc; }
		void AllocateMemory()
		{
			if (m_malloc == NULL)
				m_malloc = newRealMalloc(dlg1, workNo, size);
			m_malloc->AllocateMemory();
		}
	};


_DIALOG1.h_

	classDIALOG1 : publicCDialogEx
	{
	...
	public:
	     ...
		afx_msgvoid OnBnClickedButton1();//确认申请空间按钮
	     ...
	...
	};



_DIALOG1.cpp_

	...
	voidDIALOG1::OnBnClickedButton1()
	{
		UpdateData();	//根据控件值更新变量
		if (workSize <= 640)
		{
			//AllocateMemory(workNum, workSize);
			IMemMalloc *imalloc = newRealMallocProxy(this, workNum, workSize); //代理  
			imalloc->AllocateMemory(); //需要时由代理负责打开  
			delete imalloc;
		}
		...
	}
	...

### 5. 策略模式  
![策略](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E7%AD%96%E7%95%A5.png)  
运用于DIALOG1（动态分区分配方式对话框），DIALOG1类在AllocateMemory()中实例化一个Cache类，该Cache实例又实例化一个FIRSTFit_Algorithm类或BESTFit_Algorithm类来具体分配内存（Alloc()）。使分配内存的算法可以自由切换。避免使用多重条件判断。可扩展性良好。 

##### 主要代码：
_Strategy.h_

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

_DIALOG1.cpp_

	...
	//给某个作业分配内存并显示在展示区中
	void DIALOG1::AllocateMemory(int workNo, int size)
	{
		if (FirstFit_or_not == TRUE)
		{
			Cache cache(FIRSTFIT);
			cache.CacheAlloc(&Mem, workNo, size);
		}
		else if (BestFit_or_not == TRUE)
		{
			Cache cache(BESTFIT);
			cache.CacheAlloc(&Mem, workNo, size);
		}
		Display();
	}
	...

### 6. 迭代器模式 
![迭代器](https://github.com/DPgroup-ZG/newcode/blob/master/picture/%E8%BF%AD%E4%BB%A3%E5%99%A8.png)  
DIALOG2在打印随机数和调用页面队列时需要遍历队列，使用迭代器模式。  
Iterator提供访问和遍历元素的接口，ConcreteIterator实现迭代器接口，遍历时跟踪当前位置。Aggregate为创建相应迭代器对象的接口，ConcrteAggregate实现Aggregate。  
顺序访问聚合对象内的各个元素而无需暴露该对象的内部表示；同时为遍历不同的聚合结构提供一个统一的接口。  
  
_Iterator.h_

	classIterator
	{
	public:
		Iterator() {};
		virtual ~Iterator() {};
		virtualint First() = 0;
		virtualvoid Next() = 0;
		virtualint GetCur() = 0;
		virtualbool IsEnd() = 0;
	};

	classAggregate
	{
	public:
		virtualint Count() = 0;
		virtualvoid Push(constint& intValue) = 0;
		virtualint Pop(constint nIndex) = 0;
		virtualIterator* CreateIterator() = 0;
	};

	classConcreteIterator : publicIterator
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

	classConcreteAggregate : publicAggregate
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
				m_pIterator = newConcreteIterator(this);
			}
			return m_pIterator;
		}
		int Count()
		{
			return m_vecItems.size();
		}
		void Push(constint&intValue)
		{
			m_vecItems.push_back(intValue);
		}
		int Pop(constintnIndex)
		{
			int intRet;
			if (nIndex< Count())
			{
				intRet = m_vecItems[nIndex];
			}
			return intRet;
		}
	private:
		vector<int> m_vecItems;
		Iterator* m_pIterator;
	};


_DIALOG2.h_

	...
	classDIALOG2 : publicCDialogEx
	{
	...
	protected:
	...
	public:
		...
		//迭代器模式
		Aggregate* ca = NULL;
	     ...
		void suijishu();//产生320条随机数,显示并存储到temp[320]
		void pagestring();//显示调用的页面队列
	     ...
	};


_DIALOG2.cpp_

	...
	voidDIALOG2::suijishu()
	{
		UpdateData();	//根据控件值更新变量
		int flag = 0;
		display1 = display1 + "******按照要求产生的320个随机数：*******\r\n";

		ca = newConcreteAggregate();

		for (int i = 0; i<320; i++)
		{
			CString str;
			ca->Push(pc);

			if (flag % 2 == 0) pc = ++pc % 320;
			if (flag == 1) pc = rand() % (pc - 1);
			if (flag == 3) pc = pc + 1 + (rand() % (320 - (pc + 1)));
			flag = ++flag % 4;
			str.Format(" %03d", ca->Pop(i));
			display1 = display1 + str;
			if ((i + 1) % 10 == 0)
			{
				display1 = display1 + "\r\n";
			}
		}

		UpdateData(FALSE);				// 根据变量值更新控件
		pagestring();
	}


	voidDIALOG2::pagestring()
	{
		UpdateData();	//根据控件值更新变量
		display3 = display3 + "*****对应的调用页面队列*******\r\n";

		Iterator* iter = NULL;
		iter = ca->CreateIterator();

		if (NULL != iter) {
			while (!iter->IsEnd())
			{
				CString str;
				str.Format(" %02d", (iter->GetCur()) / 10);
				display3 = display3 + str;
				iter->Next();
			}
		}

		UpdateData(FALSE);				// 根据变量值更新控件
	}
	...


## 可执行文件
https://github.com/DPgroup-ZG/newcode/blob/master/MemoryManagement2.0.exe

## 成员工作分配比例
1：1
