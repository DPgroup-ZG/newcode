#pragma once


#include "Iterator.h"
#include <vector>
using namespace std;
#define Bsize 4
typedef struct BLOCK//����һ��������--���������
{
	int pagenum;//ҳ��
	int accessed;//�����ֶΣ���ֵ��ʾ���δ������

}BLOCK;

//�����ҳ�洢����ʽ

// DIALOG2 �Ի���

class DIALOG2 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG2)

public:
	DIALOG2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DIALOG2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:

	BLOCK block[Bsize]; //����һ��СΪ4�����������

	int pc;//�����������������¼ָ������
	int n;//ȱҳ��������������¼ȱҳ�Ĵ���	
	int select_algorithm=0;//ѡ�������û��㷨
	//������ģʽ
	Aggregate* ca = NULL;

	CString display1="";//��ʾ��Ӧ�ĵ���ҳ�����
	CString display3 = "";//��ʾ��Ӧ�ĵ���ҳ�����
	CString display2="";//��ʾ�û��㷨��

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnChangeEdit3();

	void init();     //�����ʼ������
	int findExist(int curpage);//������������Ƿ��и�ҳ��
	int findSpace();//�����Ƿ��п��������
	int findReplace();//����Ӧ���û���ҳ��
	void display();//��ʾ
	void suijishu();//����320�������
	void pagestring();//��ʾ���õ�ҳ�����
	void OPT();//OPT�㷨������û��㷨��
	void LRU();// LRU�㷨��������δʹ���û��㷨��
	void FIFO();//FIFO�㷨���Ƚ��ȳ��û��㷨��
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton2();
};


