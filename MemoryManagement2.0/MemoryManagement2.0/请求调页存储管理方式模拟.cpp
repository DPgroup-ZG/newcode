// �����ҳ�洢����ʽģ��.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "�����ҳ�洢����ʽģ��.h"
#include "afxdialogex.h"


// �����ҳ�洢����ʽģ�� �Ի���

IMPLEMENT_DYNAMIC(�����ҳ�洢����ʽģ��, CDialogEx)

�����ҳ�洢����ʽģ��::�����ҳ�洢����ʽģ��(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

�����ҳ�洢����ʽģ��::~�����ҳ�洢����ʽģ��()
{
}

void �����ҳ�洢����ʽģ��::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(�����ҳ�洢����ʽģ��, CDialogEx)
END_MESSAGE_MAP()


// �����ҳ�洢����ʽģ�� ��Ϣ�������
