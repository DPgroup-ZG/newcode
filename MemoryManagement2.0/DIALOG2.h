#pragma once


#include "Iterator.h"
#include <vector>
using namespace std;
#define Bsize 4
typedef struct BLOCK//声明一种新类型--物理块类型
{
	int pagenum;//页号
	int accessed;//访问字段，其值表示多久未被访问

}BLOCK;

//请求调页存储管理方式

// DIALOG2 对话框

class DIALOG2 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG2)

public:
	DIALOG2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DIALOG2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:

	BLOCK block[Bsize]; //定义一大小为4的物理块数组

	int pc;//程序计数器，用来记录指令的序号
	int n;//缺页计数器，用来记录缺页的次数	
	int select_algorithm=0;//选择哪种置换算法
	//迭代器模式
	Aggregate* ca = NULL;

	CString display1="";//显示对应的调用页面队列
	CString display3 = "";//显示对应的调用页面队列
	CString display2="";//显示置换算法后

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnChangeEdit3();

	void init();     //程序初始化函数
	int findExist(int curpage);//查找物理块中是否有该页面
	int findSpace();//查找是否有空闲物理块
	int findReplace();//查找应予置换的页面
	void display();//显示
	void suijishu();//产生320条随机数
	void pagestring();//显示调用的页面队列
	void OPT();//OPT算法（最佳置换算法）
	void LRU();// LRU算法（最近最久未使用置换算法）
	void FIFO();//FIFO算法（先进先出置换算法）
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton2();
};


