
// MemoryManagement2.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMemoryManagement20App: 
// �йش����ʵ�֣������ MemoryManagement2.0.cpp
//

class CMemoryManagement20App : public CWinApp
{
public:
	CMemoryManagement20App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMemoryManagement20App theApp;