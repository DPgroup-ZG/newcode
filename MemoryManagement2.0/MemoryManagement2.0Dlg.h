
// MemoryManagement2.0Dlg.h : ͷ�ļ�
//

#pragma once


// CMemoryManagement20Dlg �Ի���
class CMemoryManagement20Dlg : public CDialogEx
{
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	//	����ģʽ
	static CMemoryManagement20Dlg* GetInstance();

private:
	CMemoryManagement20Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	static CMemoryManagement20Dlg *singleton;

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

// �Ի�������
#ifdef AFX_DESIGN_TIME
enum { IDD = IDD_MEMORYMANAGEMENT20_DIALOG };
#endif