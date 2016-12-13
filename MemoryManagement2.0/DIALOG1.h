#pragma once

#include "Memory.h"

// 动态分区分配方式 

// DIALOG1 对话框

class DIALOG1 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG1)

public:
	DIALOG1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DIALOG1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:

	int	workNum;							//当前要申请内存空间的作业号
	int workSize;							//当前要申请的内存空间大小
	int	freeNum;							//当前要释放内存空间的作业号
	CString displayText;					//分区信息展示区
	BOOL FirstFit_or_not;					//是否首次适应算法
	BOOL BestFit_or_not;					//是否最佳适应算法

	afx_msg void OnBnClickedButton1();//确认申请空间按钮
	afx_msg void OnBnClickedButton2();//确认释放空间按钮
	afx_msg void OnBnClickedButton3();//开始自动演示按钮
	afx_msg void OnEnChangeEdit1();//申请作业号
	afx_msg void OnEnChangeEdit2();//申请空间大小
	afx_msg void OnEnChangeEdit3();//释放作业号
	afx_msg void OnEnChangeEdit4();//展示区
	afx_msg void OnBnClickedRadio1();//首次适应算法按钮
	afx_msg void OnBnClickedRadio2();//最佳适应算法按钮

private:
	void Display();	//显示当前分区信息
	void AllocateMemory(int workNo, int size);//分配内存
	void FreeMemory(int workNo);//释放内存

	int Step;//记录自动演示的演示步骤
	Memory Mem;//实现内存动态分区分配的类

};
