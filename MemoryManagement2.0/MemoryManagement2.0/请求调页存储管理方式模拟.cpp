// 请求调页存储管理方式模拟.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "请求调页存储管理方式模拟.h"
#include "afxdialogex.h"


// 请求调页存储管理方式模拟 对话框

IMPLEMENT_DYNAMIC(请求调页存储管理方式模拟, CDialogEx)

请求调页存储管理方式模拟::请求调页存储管理方式模拟(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

请求调页存储管理方式模拟::~请求调页存储管理方式模拟()
{
}

void 请求调页存储管理方式模拟::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(请求调页存储管理方式模拟, CDialogEx)
END_MESSAGE_MAP()


// 请求调页存储管理方式模拟 消息处理程序
