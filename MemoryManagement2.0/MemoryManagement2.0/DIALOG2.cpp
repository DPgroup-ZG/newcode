// DIALOG2.cpp : 实现文件
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include "MemoryManagement2.0.h"
#include "DIALOG2.h"
#include "afxdialogex.h"

using namespace std;

// DIALOG2 对话框

IMPLEMENT_DYNAMIC(DIALOG2, CDialogEx)

DIALOG2::DIALOG2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

DIALOG2::~DIALOG2()
{
}

void DIALOG2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, pc);
	DDX_Text(pDX, IDC_EDIT2, display1);
	DDX_Text(pDX, IDC_EDIT3, display2);
	DDX_Text(pDX, IDC_EDIT4, display3);

}


BEGIN_MESSAGE_MAP(DIALOG2, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DIALOG2::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &DIALOG2::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO1, &DIALOG2::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &DIALOG2::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &DIALOG2::OnBnClickedRadio3)
	ON_EN_CHANGE(IDC_EDIT3, &DIALOG2::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG2::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT4, &DIALOG2::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON2, &DIALOG2::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL DIALOG2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单(对话框左上角图标点开后的菜单)中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO:  在此添加额外的初始化代码
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//把OPT的按钮设为默认按下状态

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void DIALOG2::init()
{
	for (int i = 0; i<Bsize; i++)
	{
		block[i].pagenum = -1;
		block[i].accessed = 0;
		pc = n = 0;
	}
}

int DIALOG2::findExist(int curpage)
{

	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum == curpage)
			return i;//检测到内存中有该页面，返回block中的位置
	}
	return -1;
}

int DIALOG2::findSpace()
{
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum == -1)
			return i;//找到空闲的block，返回block中的位置
	}

	return -1;

}

int DIALOG2::findReplace()
{
	int pos = 0;
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].accessed >block[pos].accessed)
			pos = i;//找到应予置换页面，返回BLOCK中位置
	}
	return pos;
}

void DIALOG2::display()
{
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum != -1)
		{
			CString str;
			str.Format(" %02d", block[i].pagenum);
			//printf(" %02d", block[i].pagenum);
			display2 = display2 + str;
		}
	}
	display2 = display2 + "\r\n";
}

void DIALOG2::suijishu()
{
	UpdateData();	//根据控件值更新变量
	int flag = 0;
//	cin >> pc;
	display1 = display1 + "******按照要求产生的320个随机数：*******\r\n";
	for (int i = 0; i<320; i++)
	{
		CString str;
		temp[i] = pc;
		if (flag % 2 == 0) pc = ++pc % 320;
		if (flag == 1) pc = rand() % (pc - 1);
		if (flag == 3) pc = pc + 1 + (rand() % (320 - (pc + 1)));
		flag = ++flag % 4;
		str.Format(" %03d", temp[i]);
		display1 = display1 + str;
		//printf(" %03d", temp[i]);
		if ((i + 1) % 10 == 0) 
		{ 
			display1=display1 + "\r\n";
		}
	}
	UpdateData(FALSE);				// 根据变量值更新控件
	pagestring();
}

void DIALOG2::pagestring()
{
	UpdateData();	//根据控件值更新变量
	display3 = display3 + "*****对应的调用页面队列*******\r\n";
	//cout << "*****对应的调用页面队列*******" << endl;
	for (int i = 0; i<320; i++)
	{
		CString str;
		str.Format(" %02d", temp[i] / 10);
		//printf(" %02d", temp[i] / 10);
		display3 = display3 + str;
		if ((i + 1) % 10 == 0) {
			display3 = display3 + "\r\n";
		}
	}
	UpdateData(FALSE);				// 根据变量值更新控件
}

void DIALOG2::OPT()
{
	UpdateData();	//根据控件值更新变量
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;
		exist = findExist(curpage);
		if (exist == -1)
		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				for (int k = 0; k<Bsize; k++)
				{
					for (int j = i; j<320; j++)
					{
						if (block[k].pagenum != temp[j] / 10)
						{
							block[k].accessed = 1000;
						}//将来不会用，设置为一个很大数
						else
						{
							block[k].accessed = j;
							break;

						}
					}
				}
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;

			}
		}
	}
	CString str1,str2;
	str1.Format("%d",n);
	str2.Format("%.4f", (n / 320.0) * 100);
	display2 = display2 + "缺页次数:" + str1 + "\r\n";
	//cout << "缺页次数:" << n << endl;
	display2 = display2 +"缺页率:"+ str2+ "%"+ "\r\n";
	//cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;

	UpdateData(FALSE);				// 根据变量值更新控件
}

void DIALOG2::LRU()
{
	UpdateData();	//根据控件值更新变量
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;
		exist = findExist(curpage);
		if (exist == -1)
		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;

			}
		}
		else block[exist].accessed = -1;//恢复存在的并刚访问过的BLOCK中页面accessed为-1
		for (int j = 0; j<4; j++)
		{
			block[j].accessed++;
		}

	}
	CString str1, str2;
	str1.Format("%d", n);
	str2.Format("%.4f", (n / 320.0) * 100);
	display2 = display2 + "缺页次数:" + str1 + "\r\n";
	//cout << "缺页次数:" << n << endl;
	display2 = display2 + "缺页率:" + str2 + "%" + "\r\n";
	//cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;

	UpdateData(FALSE);				// 根据变量值更新控件
}

void DIALOG2::FIFO()
{
	UpdateData();	//根据控件值更新变量
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;

		exist = findExist(curpage);
		if (exist == -1)

		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;
				block[position].accessed--;
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].accessed++;


	}
	CString str1, str2;
	str1.Format("%d", n);
	str2.Format("%.4f", (n / 320.0) * 100);
	display2 = display2 + "缺页次数:" + str1 + "\r\n";
	//cout << "缺页次数:" << n << endl;
	display2 = display2 + "缺页率:" + str2 + "%" + "\r\n";
	//cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;

	UpdateData(FALSE);				// 根据变量值更新控件
}

// DIALOG2 消息处理程序


void DIALOG2::OnEnChangeEdit1()
{

}


void DIALOG2::OnEnChangeEdit2()
{

}

void DIALOG2::OnEnChangeEdit3()
{

}

void DIALOG2::OnEnChangeEdit4()
{

}

void DIALOG2::OnBnClickedRadio1()
{
	select_algorithm = 0;
}


void DIALOG2::OnBnClickedRadio2()
{
	select_algorithm = 1;
}


void DIALOG2::OnBnClickedRadio3()
{
	select_algorithm = 2;
}

void DIALOG2::OnBnClickedButton1()
{
	suijishu();
}

void DIALOG2::OnBnClickedButton2()
{
	switch (select_algorithm)
	{
	case 0:
		init();
		display2 = display2 + "最佳置换算法OPT:\r\n";
		OPT();
		break;
	case 1:
		init();
		display2 = display2 + "最近最久未使用置换算法LRU:\r\n";
		LRU();
		break;
	case 2:
		init();
		display2 = display2 + "先进先出置换算法FIFO:\r\n";
		FIFO();
		break;

	default:;
	}
}
