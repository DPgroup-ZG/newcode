#pragma once


// 请求调页存储管理方式模拟 对话框

class DIALOG2 : public CDialogEx
{
	DECLARE_DYNAMIC(请求调页存储管理方式模拟)

public:
	请求调页存储管理方式模拟(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~请求调页存储管理方式模拟();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
