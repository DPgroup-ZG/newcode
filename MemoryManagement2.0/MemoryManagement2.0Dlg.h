
// MemoryManagement2.0Dlg.h : 头文件
//

#pragma once


// CMemoryManagement20Dlg 对话框
class CMemoryManagement20Dlg : public CDialogEx
{
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	//	单例模式
	static CMemoryManagement20Dlg* GetInstance();

private:
	CMemoryManagement20Dlg(CWnd* pParent = NULL);	// 标准构造函数
	static CMemoryManagement20Dlg *singleton;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};

// 对话框数据
#ifdef AFX_DESIGN_TIME
enum { IDD = IDD_MEMORYMANAGEMENT20_DIALOG };
#endif