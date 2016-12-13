#pragma once

#include "Memory.h"

// ��̬�������䷽ʽ 

// DIALOG1 �Ի���

class DIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG1)

public:
	DIALOG1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DIALOG1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:

	int	workNum;							//��ǰҪ�����ڴ�ռ����ҵ��
	int workSize;							//��ǰҪ������ڴ�ռ��С
	int	freeNum;							//��ǰҪ�ͷ��ڴ�ռ����ҵ��
	CString displayText;					//������Ϣչʾ��
	BOOL FirstFit_or_not;					//�Ƿ��״���Ӧ�㷨
	BOOL BestFit_or_not;					//�Ƿ������Ӧ�㷨

	afx_msg void OnBnClickedButton1();//ȷ������ռ䰴ť
	afx_msg void OnBnClickedButton2();//ȷ���ͷſռ䰴ť
	afx_msg void OnBnClickedButton3();//��ʼ�Զ���ʾ��ť
	afx_msg void OnEnChangeEdit1();//������ҵ��
	afx_msg void OnEnChangeEdit2();//����ռ��С
	afx_msg void OnEnChangeEdit3();//�ͷ���ҵ��
	afx_msg void OnEnChangeEdit4();//չʾ��
	afx_msg void OnBnClickedRadio1();//�״���Ӧ�㷨��ť
	afx_msg void OnBnClickedRadio2();//�����Ӧ�㷨��ť

private:
	void Display();	//��ʾ��ǰ������Ϣ
	void AllocateMemory(int workNo, int size);//�����ڴ�
	void FreeMemory(int workNo);//�ͷ��ڴ�

	int Step;//��¼�Զ���ʾ����ʾ����
	Memory Mem;//ʵ���ڴ涯̬�����������

};
