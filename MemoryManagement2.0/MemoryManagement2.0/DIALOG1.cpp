// DIALOG1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "MemoryManagement2.0.h"
#include "MemoryManagement2.0Dlg.h"
#include "DIALOG1.h"
#include "afxdialogex.h"


// DIALOG1 �Ի���

IMPLEMENT_DYNAMIC(DIALOG1, CDialogEx)

DIALOG1::DIALOG1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	workNum = 0;
	workSize = 0;
	freeNum = 0;
	displayText = "";
	//}}AFX_DATA_INIT
	FirstFit_or_not = TRUE; //δѡ�������£�Ĭ�����״���Ӧ�㷨
	BestFit_or_not = FALSE;
	Step = 0;
	Mem.AllocateTotalSize(640);	// ����640KB���ڴ�ռ�

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


// DIALOG1 ��Ϣ�������
BOOL DIALOG1::OnInitDialog()
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
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//���״���Ӧ�㷨�İ�ť��ΪĬ�ϰ���״̬

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void DIALOG1::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR DIALOG1::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void DIALOG1::OnEnChangeEdit1()//������ҵ��
{}
void DIALOG1::OnEnChangeEdit2()//����ռ��С
{}
void DIALOG1::OnEnChangeEdit3()//�ͷ���ҵ��
{}
void DIALOG1::OnEnChangeEdit4()//չʾ��
{
}


//�״���Ӧ�㷨��ť
void DIALOG1::OnBnClickedRadio1()
{
	FirstFit_or_not = TRUE;
	BestFit_or_not = FALSE;
}

//�����Ӧ�㷨��ť
void DIALOG1::OnBnClickedRadio2()
{
	FirstFit_or_not = FALSE;
	BestFit_or_not = TRUE;
}

//ȷ������ռ䰴ť
void DIALOG1::OnBnClickedButton1()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	if (workSize <= 640)
	{
		AllocateMemory(workNum, workSize);
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
	}
}

//ȷ���ͷſռ䰴ť
void DIALOG1::OnBnClickedButton2()
{
	UpdateData();//���ݿؼ�ֵ���±���
	FreeMemory(freeNum);
}

//��ʼ�Զ���ʾ��ť
void DIALOG1::OnBnClickedButton3()
{
	switch (Step)
	{
	case 0:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(1, 130);
		break;
	}
	case 1:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(2, 60);
		break;
	}
	case 2:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(3, 100);
		break;
	}
	case 3:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		FreeMemory(2);
		break;
	}
	case 4:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(4, 200);
		break;
	}
	case 5:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		FreeMemory(3);
		break;
	}
	case 6:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		FreeMemory(1);
		break;
	}
	case 7:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(5, 140);
		break;
	}
	case 8:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(6, 60);
		break;
	}
	case 9:
	{
		SetDlgItemText(IDC_BUTTON3, "��һ��");
		AllocateMemory(7, 50);
		break;
	}
	case 10:
	{
		SetDlgItemText(IDC_BUTTON3, "��ʼ");
		FreeMemory(6);

		//��ʾ�����ͷ��ڴ沢���·���
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


//��ĳ����ҵ�����ڴ沢��ʾ��չʾ����
void DIALOG1::AllocateMemory(int workNo, int size)
{
	if (FirstFit_or_not == TRUE)
	{
		Mem.FirstFit(workNo, size);// �״���Ӧ�㷨
	}
	else if (BestFit_or_not == TRUE)
	{
		Mem.BestFit(workNo, size);// �����Ӧ�㷨
	}
	Display();
}

//�ͷ�ĳ����ҵ���ڴ�
void DIALOG1::FreeMemory(int workNo)
{
	Mem.FreeMemory(workNo);
	Display();
}

//չʾ
void DIALOG1::Display()
{
	Node* p = Mem.GetPartitionList();//pΪͷ��㣬�޾�����Ϣ
	displayText = "��ǰ���з����������\r\n";
	displayText = displayText + "ʼĩ��ַ(KB)\t������С(KB)\t״̬\t��ҵ��\r\n";
	Node* current = p->next;//p->next���ǵ�һ���о�����Ϣ�Ľ��
	while (current != NULL)
	{
		// ��ҵ��Ϊ0�ķ����������ǿ��з���
		if (current->workNo == 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t����\t--\r\n", current->address, current->size + current->address, current->size);
			displayText = displayText + str;
		}
		// ��ҵ�ŷ�0�ķ������Ƿǿ��з���
		if (current->workNo != 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t����\t��ҵ%d\r\n", current->address, current->size + current->address, current->size, current->workNo);
			displayText = displayText + str;
		}
		current = current->next;
	}
	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}