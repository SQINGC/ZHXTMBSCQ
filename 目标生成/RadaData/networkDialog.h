#pragma once
#include "afxcmn.h"


// networkDialog 对话框

class networkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(networkDialog)

public:
	networkDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~networkDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	CIPAddressCtrl localAddress;
	afx_msg void OnEnChangeEdit1();
	CIPAddressCtrl targetAddress;
	afx_msg void OnBnClickedOk();
};
