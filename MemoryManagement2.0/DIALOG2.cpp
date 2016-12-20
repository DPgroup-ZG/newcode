// DIALOG2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include "MemoryManagement2.0.h"
#include "DIALOG2.h"
#include "afxdialogex.h"
#include "State.h"
#include "Iterator.h"

using namespace std;

// DIALOG2 �Ի���

IMPLEMENT_DYNAMIC(DIALOG2, CDialogEx)

DIALOG2::DIALOG2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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

	// ��������...���˵�����ӵ�ϵͳ�˵�(�Ի������Ͻ�ͼ��㿪��Ĳ˵�)�С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//��OPT�İ�ť��ΪĬ�ϰ���״̬

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void DIALOG2::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR DIALOG2::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
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
			return i;//��⵽�ڴ����и�ҳ�棬����block�е�λ��
	}
	return -1;
}

int DIALOG2::findSpace()
{
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum == -1)
			return i;//�ҵ����е�block������block�е�λ��
	}

	return -1;

}

int DIALOG2::findReplace()
{
	int pos = 0;
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].accessed >block[pos].accessed)
			pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
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
			display2 = display2 + str;
		}
	}
	display2 = display2 + "\r\n";
}

void DIALOG2::suijishu()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	int flag = 0;
	display1 = display1 + "******����Ҫ�������320���������*******\r\n";

	ca = new ConcreteAggregate();

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

	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
	pagestring();
}


void DIALOG2::pagestring()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	display3 = display3 + "*****��Ӧ�ĵ���ҳ�����*******\r\n";

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

	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}

void DIALOG2::OPT()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		//pc = temp[i];
		pc=ca->Pop(i);
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
						//if (block[k].pagenum != temp[j] / 10)
						if(block[k].pagenum!= ca->Pop(j)/10)
						{
							block[k].accessed = 1000;
						}//���������ã�����Ϊһ���ܴ���
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
	display2 = display2 + "ȱҳ����:" + str1 + "\r\n";
	display2 = display2 +"ȱҳ��:"+ str2+ "%"+ "\r\n";

	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}

void DIALOG2::LRU()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		//pc = temp[i];
		pc = ca->Pop(i);
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
		else block[exist].accessed = -1;//�ָ����ڵĲ��շ��ʹ���BLOCK��ҳ��accessedΪ-1
		for (int j = 0; j<4; j++)
		{
			block[j].accessed++;
		}

	}
	CString str1, str2;
	str1.Format("%d", n);
	str2.Format("%.4f", (n / 320.0) * 100);
	display2 = display2 + "ȱҳ����:" + str1 + "\r\n";
	display2 = display2 + "ȱҳ��:" + str2 + "%" + "\r\n";

	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}

void DIALOG2::FIFO()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		//pc = temp[i];
		pc = ca->Pop(i);
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
	display2 = display2 + "ȱҳ����:" + str1 + "\r\n";
	display2 = display2 + "ȱҳ��:" + str2 + "%" + "\r\n";

	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}

// DIALOG2 ��Ϣ�������


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


//״̬ģʽ
void DIALOG2::OnBnClickedButton2()
{
	RealRun *relr;
	switch (select_algorithm)
	{
	case 0:
		init();
		display2 = display2 + "����û��㷨OPT:\r\n";
		relr = new RealRun(new OPTState(), this);
		relr->GetState();
		delete relr;
		break;
	case 1:
		init();
		display2 = display2 + "������δʹ���û��㷨LRU:\r\n";
		relr = new RealRun(new LRUState(), this);
		relr->GetState();
		delete relr;
		break;
	case 2:
		init();
		display2 = display2 + "�Ƚ��ȳ��û��㷨FIFO:\r\n";
		relr = new RealRun(new FIFOState(), this);
		relr->GetState();
		delete relr;
		break;
	default:;
	}
}
