// DIALOG1.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "MemoryManagement2.0Dlg.h"
#include "DIALOG1.h"
#include "afxdialogex.h"


// DIALOG1 对话框

IMPLEMENT_DYNAMIC(DIALOG1, CDialogEx)

DIALOG1::DIALOG1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	workNum = 0;
	workSize = 0;
	freeNum = 0;
	displayText = "";
	//}}AFX_DATA_INIT
	FirstFit_or_not = TRUE; //未选择的情况下，默认是首次适应算法
	BestFit_or_not = FALSE;
	Step = 0;
	Mem.AllocateTotalSize(640);	// 分配640KB的内存空间

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

DIALOG1::~DIALOG1()
{
}

void DIALOG1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, workSize);
	DDV_MinMaxLong(pDX, workSize, 0, 640);
	DDX_Text(pDX, IDC_EDIT3, freeNum);
	DDX_Text(pDX, IDC_EDIT1, workNum);
	DDX_Text(pDX, IDC_EDIT4, displayText);
}


BEGIN_MESSAGE_MAP(DIALOG1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &DIALOG1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &DIALOG1::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &DIALOG1::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &DIALOG1::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &DIALOG1::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &DIALOG1::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_RADIO1, &DIALOG1::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &DIALOG1::OnBnClickedRadio2)
END_MESSAGE_MAP()


// DIALOG1 消息处理程序
BOOL DIALOG1::OnInitDialog()
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
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//把首次适应算法的按钮设为默认按下状态

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//void DIALOG1::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
//		CDialogEx::OnSysCommand(nID, lParam);
//	}
//}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void DIALOG1::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR DIALOG1::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void DIALOG1::OnEnChangeEdit1()//申请作业号
{}
void DIALOG1::OnEnChangeEdit2()//申请空间大小
{}
void DIALOG1::OnEnChangeEdit3()//释放作业号
{}
void DIALOG1::OnEnChangeEdit4()//展示区
{
}


//首次适应算法按钮
void DIALOG1::OnBnClickedRadio1()
{
	FirstFit_or_not = TRUE;
	BestFit_or_not = FALSE;
}

//最佳适应算法按钮
void DIALOG1::OnBnClickedRadio2()
{
	FirstFit_or_not = FALSE;
	BestFit_or_not = TRUE;
}

//确认申请空间按钮
void DIALOG1::OnBnClickedButton1()
{
	UpdateData();	//根据控件值更新变量
	if (workSize <= 640)
	{
		AllocateMemory(workNum, workSize);
	}
	else
	{
		AfxMessageBox("申请内存失败!");
	}
}

//确认释放空间按钮
void DIALOG1::OnBnClickedButton2()
{
	UpdateData();//根据控件值更新变量
	FreeMemory(freeNum);
}

//开始自动演示按钮
void DIALOG1::OnBnClickedButton3()
{
	switch (Step)
	{
	case 0:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(1, 130);
		break;
	}
	case 1:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(2, 60);
		break;
	}
	case 2:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(3, 100);
		break;
	}
	case 3:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		FreeMemory(2);
		break;
	}
	case 4:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(4, 200);
		break;
	}
	case 5:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		FreeMemory(3);
		break;
	}
	case 6:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		FreeMemory(1);
		break;
	}
	case 7:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(5, 140);
		break;
	}
	case 8:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(6, 60);
		break;
	}
	case 9:
	{
		SetDlgItemText(IDC_BUTTON3, "下一步");
		AllocateMemory(7, 50);
		break;
	}
	case 10:
	{
		SetDlgItemText(IDC_BUTTON3, "开始");
		FreeMemory(6);

		//演示结束释放内存并重新分配
		Mem.Free();
		Mem.AllocateTotalSize(640);
		break;
	}
	default:
	{
		break;
	}
	}
	Step = (Step + 1) % 11;

}


//给某个作业分配内存并显示在展示区中
void DIALOG1::AllocateMemory(int workNo, int size)
{
	if (FirstFit_or_not == TRUE)
	{
		Mem.FirstFit(workNo, size);// 首次适应算法
	}
	else if (BestFit_or_not == TRUE)
	{
		Mem.BestFit(workNo, size);// 最佳适应算法
	}
	Display();
}

//释放某个作业的内存
void DIALOG1::FreeMemory(int workNo)
{
	Mem.FreeMemory(workNo);
	Display();
}

//展示
void DIALOG1::Display()
{
	Node* p = Mem.GetPartitionList();//p为头结点，无具体信息
	displayText = "当前空闲分区链情况：\r\n";
	displayText = displayText + "始末地址(KB)\t分区大小(KB)\t状态\t作业名\r\n";
	Node* current = p->next;//p->next才是第一个有具体信息的结点
	while (current != NULL)
	{
		// 作业号为0的分区，表明是空闲分区
		if (current->workNo == 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t空闲\t--\r\n", current->address, current->size + current->address, current->size);
			displayText = displayText + str;
		}
		// 作业号非0的分区，是非空闲分区
		if (current->workNo != 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t已用\t作业%d\r\n", current->address, current->size + current->address, current->size, current->workNo);
			displayText = displayText + str;
		}
		current = current->next;
	}
	UpdateData(FALSE);				// 根据变量值更新控件
}