// ��̬�������䷽ʽ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "��̬�������䷽ʽ.h"
#include "afxdialogex.h"


// ��̬�������䷽ʽ �Ի���

IMPLEMENT_DYNAMIC(��̬�������䷽ʽ, CDialogEx)

��̬�������䷽ʽ::��̬�������䷽ʽ(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

��̬�������䷽ʽ::~��̬�������䷽ʽ()
{
}

void ��̬�������䷽ʽ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(��̬�������䷽ʽ, CDialogEx)
END_MESSAGE_MAP()


// ��̬�������䷽ʽ ��Ϣ�������
