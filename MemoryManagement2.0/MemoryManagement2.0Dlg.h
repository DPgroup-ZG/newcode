
// MemoryManagement2.0Dlg.h : ͷ�ļ�
//

#pragma once


// CMemoryManagement20Dlg �Ի���
class CMemoryManagement20Dlg : public CDialogEx
{
// ����
public:
	CMemoryManagement20Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMORYMANAGEMENT20_DIALOG };
#endif

// ʵ��
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
