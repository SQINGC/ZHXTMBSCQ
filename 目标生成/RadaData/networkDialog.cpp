// networkDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RadaData.h"
#include "networkDialog.h"
#include "afxdialogex.h"


// networkDialog �Ի���

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


// networkDialog ��Ϣ�������


void networkDialog::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void networkDialog::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void networkDialog::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	MessageBox(_T("�ù��ܲ�����..."),_T("��ʾ"),1);
}
