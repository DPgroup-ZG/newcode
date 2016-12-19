#ifndef SINGLE_H_
#define SINGLE_H_

#include "DIALOG1.h"
#include "DIALOG2.h"

//	工厂模式
enum CTYPE { DIALOG_1, DIALOG_2 };
class SingleCore
{
public:
	virtual void Show() = 0;
};


class SingleCoreA : public SingleCore
{
public:
	void Show() 
	{
		DIALOG1 dlg1;
		dlg1.DoModal();
	}
};


class SingleCoreB : public SingleCore
{
public:
	void Show() 
	{
		DIALOG2 dlg2;
		dlg2.DoModal();
	}
};


class Factory
{
public:
	SingleCore* CreateSingleCore(enum CTYPE ctype)
	{
		if (ctype == DIALOG_1) //工厂内部判断  
			return new SingleCoreA();   
		else if (ctype == DIALOG_2)
			return new SingleCoreB();
		else
			return NULL;
	}
};

#endif