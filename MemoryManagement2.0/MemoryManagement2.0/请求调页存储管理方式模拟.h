#pragma once


// �����ҳ�洢����ʽģ�� �Ի���

class DIALOG2 : public CDialogEx
{
	DECLARE_DYNAMIC(�����ҳ�洢����ʽģ��)

public:
	�����ҳ�洢����ʽģ��(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~�����ҳ�洢����ʽģ��();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
