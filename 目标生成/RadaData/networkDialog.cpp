// networkDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "RadaData.h"
#include "networkDialog.h"
#include "afxdialogex.h"


// networkDialog 对话框

IMPLEMENT_DYNAMIC(networkDialog, CDialogEx)

networkDialog::networkDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(networkDialog::IDD, pParent)
{

}

networkDialog::~networkDialog()
{
}

void networkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, localAddress);
	DDX_Control(pDX, IDC_IPADDRESS2, targetAddress);
	localAddress.SetAddress(192, 168, 0, 1);
	targetAddress.SetAddress(255, 255, 255, 255);
}


BEGIN_MESSAGE_MAP(networkDialog, CDialogEx)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &networkDialog::OnIpnFieldchangedIpaddress1)
	ON_EN_CHANGE(IDC_EDIT1, &networkDialog::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &networkDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// networkDialog 消息处理程序


void networkDialog::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void networkDialog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void networkDialog::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	MessageBox(_T("该功能测试中..."),_T("提示"),1);
}
