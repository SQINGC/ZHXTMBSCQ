#pragma once
#include "afxcmn.h"


// networkDialog �Ի���

class networkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(networkDialog)

public:
	networkDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~networkDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	CIPAddressCtrl localAddress;
	afx_msg void OnEnChangeEdit1();
	CIPAddressCtrl targetAddress;
	afx_msg void OnBnClickedOk();
};
