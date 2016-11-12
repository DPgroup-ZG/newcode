// 动态分区分配方式.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "动态分区分配方式.h"
#include "afxdialogex.h"


// 动态分区分配方式 对话框

IMPLEMENT_DYNAMIC(动态分区分配方式, CDialogEx)

动态分区分配方式::动态分区分配方式(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

动态分区分配方式::~动态分区分配方式()
{
}

void 动态分区分配方式::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(动态分区分配方式, CDialogEx)
END_MESSAGE_MAP()


// 动态分区分配方式 消息处理程序
