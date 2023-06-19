
// RadaDataDlg.cpp : ʵ���ļ�
//
#include"glew.h"
#include "stdafx.h"
#include "RadaData.h"
#include "RadaDataDlg.h"
#include "afxdialogex.h"
#include "typeDefine.h"
#include "situInitStruct.h"
#include<stdio.h>
#include <vector>
#include "resource.h"
#include "math.h"
#include <gl.h>
#include <glu.h>
#include <glut.h>
#include"coordinate.h"

#include <glaux.h>



#pragma comment(lib,"glaux.lib")   //��glaux.lib���ӵ�����

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BUFSIZE 10240
#define PI 3.14159265

SOCKET recvSocket = INVALID_SOCKET;//�׽��ֽ���

TargetIndRadarInfo TargetInfo;
SearchRadarInfo SearchInfo;

vector<TargetDetectInfo> TargetDetInfoT;
vector<TargetDetectInfo> TargetDetInfoS;

double zt[12] = { 3000, -10000, -15000, -10000, -20000, 15000, -10000, 15000, 10000, 8000 };//��ʼz�����λ��
double xt[12] = { 1000, -1000, 1000, 20000, -25000, -18000, 15000, 10000, -13000, 8000 };//��ʼx�����λ��
double yt[12] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };//��ʼy�����λ��

double vzt[12] = { -200, 200, 200, 200, 200, -200, 200, -200, -200, -200 };//��ʼz������ٶ�
double vxt[12] = { -200, 0, 0, -200, 200, 200, -200, -200, 0, 200 };//��ʼx������ٶ�
double vyt[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//��ʼy������ٶ�
double vztnew[12] = { -100, 200, 200, 200, 200, -200, 200, -200, -200, -200 };

double zs[10] = { /*-1628.186523*/0, -2678.660156, -1102.949219, -2187.406250, 1068.965820, -1026.949158, 1373.813477, -1221.389648, -1528.186523, -257.660156 };//��֪�������
double xs[10] = { /*2028.720703*/0, 2221.796875, 3023.755859, -770.307617, 1731.691406, -2151.496094, -1119.811523, 534.475525, 2128.720703, 232.796875 };		//��֪�������
double ys[10] = { 50.000000, 50.000000, 50.000000, 50.000000, 50.000000, 50.000000, 50.000000, 50.000000, 50.000000, 50.000000 };							//��֪�������

double vzs = -15, vxs = -15, vys = 0;//???

double omiga = 0.01;


double ax1 = 20;
double az1 = 5;


int TarNumT = 0;
int TarNumS = 0;

int SradarId[3] = { 20202, 20203, 20302 };

int kId = 0;

short DamageINT;//Ŀ�����ID
short FreeGun;//���л���ID

int shanshuo = 0;

vector<vector<TargetDetectInfo>> TargetSence;

double dx = 0;//ɨ����ת�Ƕ�

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRadaDataDlg �Ի���

CRadaDataDlg::~CRadaDataDlg()
{
	closesocket(sendSocket);         //�رռ���socket
	WSACleanup();
}

CRadaDataDlg::CRadaDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRadaDataDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_GLPixelIndex = 0;
	cmb1flag = 0;
	planeflag = 1;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			hj1[j][i][0] = 0.0;
			hj1[j][i][1] = 0.0;
			R[i] = 0.0;
			theta[i] = 0.0;
		}
	}
}

void CRadaDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_tar);


	DDX_Control(pDX, IDC_LIST4, m_listmuzhi);
}

BEGIN_MESSAGE_MAP(CRadaDataDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRadaDataDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRadaDataDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDCANCEL, &CRadaDataDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CRadaDataDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CRadaDataDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_TUICHU, &CRadaDataDlg::OnBnClickedTuichu)
	ON_BN_CLICKED(IDC_BUTTON5, &CRadaDataDlg::OnBnClickedButton5)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRadaDataDlg ��Ϣ�������

BOOL CRadaDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//�����豸����������ɫ������
	m_Brush.CreateSolidBrush(RGB(255, 0, 0));
	CWnd *pWnd = GetDlgItem(IDC_STATIC);
	hDC = ::GetDC(pWnd->GetSafeHwnd());
	if (SetWindowPixelFormat(hDC) == FALSE)
		return 0;
	if (CreateViewGLRC(hDC) == FALSE)
		return 0;
	
	

	CDialogEx::SetBackgroundColor(RGB(79, 79, 79));//���屳������

	


	WSADATA wsaData;                                   //ָ��WinSocket��Ϣ�ṹ��ָ��
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)           //����WinSocket�ĳ�ʼ��
	{
		printf("Can't initiates windows socket!Program stop.\n");//��ʼ��ʧ�ܷ���-1 
	}
	TargetDetInfoT.resize(12);
	for (int i = 0; i < 10; ++i)
	{
		TargetDetInfoT[i].targetNo = 1 + i;
		TargetDetInfoT[i].targetId = 3001 + i;
		TargetDetInfoT[i].trackTime = 1;
		TargetDetInfoT[i].x = xt[i];
		TargetDetInfoT[i].y = yt[i];
		TargetDetInfoT[i].z = zt[i];
		TargetDetInfoT[i].Vx = vxt[i];
		TargetDetInfoT[i].Vy = vyt[i];
		TargetDetInfoT[i].Vz = vzt[i];
		TargetDetInfoT[i].yaw = 9;
		TargetDetInfoT[i].pitch = 9;
		TargetDetInfoT[i].detectionDistance = 500;
	}

	TargetDetInfoS.resize(12);
	for (int i = 0; i < 12; ++i)
	{

		TargetDetInfoS[i].targetNo = 11 + i;
		TargetDetInfoS[i].targetId = 3001 + i;
		TargetDetInfoS[i].trackTime = 1;
		TargetDetInfoS[i].x = xs[i];
		TargetDetInfoS[i].y = ys[i];
		TargetDetInfoS[i].z = zs[i];
		TargetDetInfoS[i].Vx = vxs;
		TargetDetInfoS[i].Vy = vys;
		TargetDetInfoS[i].Vz = vzs;
		TargetDetInfoS[i].yaw = 9;
		TargetDetInfoS[i].pitch = 9;
		TargetDetInfoS[i].detectionDistance = 500;
	}

	m_tar.InsertString(0, _T("1"));//Ŀָ�״�
	m_tar.InsertString(1, _T("2"));
	m_tar.InsertString(2, _T("3"));
	m_tar.InsertString(3, _T("4"));
	m_tar.InsertString(4, _T("5"));
	m_tar.InsertString(5, _T("6"));//Ŀָ�״�
	m_tar.InsertString(6, _T("7"));
	m_tar.InsertString(7, _T("8"));
	m_tar.InsertString(8, _T("9"));
	m_tar.InsertString(9, _T("10"));

	SetDlgItemText(IDC_COMBO1, "");



	ThreadFlag = FALSE;


	//Ŀָ�״��б�
	LONG lStyle1;
	lStyle1 = GetWindowLong(m_listmuzhi.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle1 &= ~LVS_TYPEMASK;//�����ʾ��ʽλ
	lStyle1 |= LVS_REPORT;//����style
	lStyle1 |= LVS_SINGLESEL;//���õ�ѡģʽ
	SetWindowLong(m_listmuzhi.m_hWnd, GWL_STYLE, lStyle1);//����style
	DWORD dwStyle1 = m_listmuzhi.GetExtendedStyle();
	dwStyle1 |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и���
	dwStyle1 |= LVS_EX_GRIDLINES;//������
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listmuzhi.SetExtendedStyle(dwStyle1);

	m_listmuzhi.InsertColumn(0, "Ŀ������", LVCFMT_LEFT, 60);
	m_listmuzhi.InsertColumn(1, "Ŀ��ID", LVCFMT_LEFT, 60);
	m_listmuzhi.InsertColumn(2, "ʱ��", LVCFMT_LEFT, 60);
	m_listmuzhi.InsertColumn(3, "x", LVCFMT_LEFT, 50);
	m_listmuzhi.InsertColumn(4, "y", LVCFMT_LEFT, 50);
	m_listmuzhi.InsertColumn(5, "z", LVCFMT_LEFT, 80);
	m_listmuzhi.InsertColumn(6, "vx", LVCFMT_LEFT, 100);
	m_listmuzhi.InsertColumn(7, "vy", LVCFMT_LEFT, 100);
	m_listmuzhi.InsertColumn(8, "vz", LVCFMT_LEFT, 100);
	m_listmuzhi.InsertColumn(9, "��λ��", LVCFMT_LEFT, 100);
	m_listmuzhi.InsertColumn(10, "�ߵͽ�", LVCFMT_LEFT, 100);
	m_listmuzhi.InsertColumn(11, "����", LVCFMT_LEFT, 100);

	dx = PI / 2;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRadaDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRadaDataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(79, 79, 79));
		CDialogEx::OnPaint();
	}

	SetWindowText(_T("Ŀ��������"));
	//�����ӽǣ���ʹ�ô��ڸı�ʱͼ�β���
	Reshape();
	//���û�ͼ����
	DrawOpenGL();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRadaDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







void CRadaDataDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int UDP_PORT2 = 3000;
	SOCKADDR_IN saUdpServ;                              //ָ��ͨ�Ŷ���Ľṹ��ָ�� 
	BOOL fBroadcast = TRUE;
	sendSocket = socket(PF_INET, SOCK_DGRAM, 0);
	setsockopt(sendSocket, SOL_SOCKET, SO_BROADCAST, (CHAR *)&fBroadcast, sizeof(BOOL));
	//  �������ã�ע��Ҫ��IP��ַ��ΪINADDR_BROADCAST����ʾ���͹㲥UDP���ݱ�
	saUdpServ.sin_family = AF_INET;
	saUdpServ.sin_addr.s_addr = htonl(INADDR_BROADCAST);// htonl(INADDR_ANY);
	saUdpServ.sin_port = htons(UDP_PORT2);               //�����õĶ˿ڣ����Ը�����Ҫ����
	MessageHeader mess;//
	MessageHeader messS;//
	char sendBuf[BUFSIZE];
	char sendBufS[BUFSIZE];
	int lenT = 0;
	int lenS = 0;
	CString tarno, tarid, time, x, y, z, vx, vy, vz, yaw, pitch, distance;

	switch (nIDEvent)
	{
	case 1:
		//Ŀָ�״�	
		mess.dataType = 3;		        // ��������
		mess.nodeID = 301;		        // �ڵ�ID
		mess.sourceID = 10101;		    // ���ͷ�ID
		mess.childDataType = 18;		// ��������
		mess.dataLen = 0;		        // ���������ֽڳ���
		mess.serialNumber = 1;	        // ������ˮ��
		mess.time = 1;			        // ʱ���
		mess.version = 1;		        // �汾��

		TargetInfo.radarAzimuth = 1;
		TargetInfo.radarHeightangle = 1;
		TargetInfo.radarTrackDim = 1;
		TargetInfo.targetNumber = 4;

		memset(sendBuf, 0, BUFSIZE);
		mess.dataLen = sizeof(TargetInfo) + 4 * sizeof(TargetDetectInfo);
		memcpy(sendBuf, &mess, sizeof(mess));
		memcpy(sendBuf + sizeof(mess), &TargetInfo, sizeof(TargetInfo));

		/************************************************************************************************************************************************/
		if (TarNumT>=0)//��Ŀ��
		{
			/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
			for (int i = 0; i < 1+TarNumT; i++)
			{
				///*�����������������������������������Ե�һ���߽��е�����ģ����������������������������������������������������������������������������������������*/
				//if (i == 0) //
				//{
				//	/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
				//	if (TargetDetInfoT[i].trackTime >= 1)//ʱ�����1ʱ
				//	{
				//		memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i * sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));//��sendBuf���Ѿ�����
				//		//��mess��TargetInfo��
				//		//����֮ǰ�ĵ�ַ���ܴ���
				//		//��Ȼ�͸�����
				//		//vxt[i] = vxt[i] + ax1;
				//		//vzt[i] = vzt[i] + az1;

				//		TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
				//		TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
				//		TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
				//		TargetDetInfoT[i].trackTime++;
				//		TargetSence[i].push_back(TargetDetInfoT[i]);
				//		///////�б���ʾ
				//		tarno.Format("%d", TargetDetInfoT[i].targetNo);
				//		tarid.Format("%d", TargetDetInfoT[i].targetId);
				//		time.Format("%lf", TargetDetInfoT[i].trackTime);
				//		x.Format("%lf", TargetDetInfoT[i].x);
				//		y.Format("%lf", TargetDetInfoT[i].y);
				//		z.Format("%lf", TargetDetInfoT[i].z);
				//		vx.Format("%lf", TargetDetInfoT[i].Vx);
				//		vy.Format("%lf", TargetDetInfoT[i].Vy);
				//		vz.Format("%lf", TargetDetInfoT[i].Vz);
				//		yaw.Format("%d", TargetDetInfoT[i].yaw);
				//		pitch.Format("%d", TargetDetInfoT[i].pitch);
				//		distance.Format("%lf", TargetDetInfoT[i].detectionDistance);
				//	}
				//	/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
				//	else//�൱�ڳ�ʼ��
				//	{
				//		//memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i * sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));
				//		//TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
				//		//TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
				//		//TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
				//		//TargetDetInfoT[i].trackTime++;
				//		//TargetSence[i].push_back(TargetDetInfoT[i]);
				//		/////////�б���ʾ
				//		//tarno.Format("%d", TargetDetInfoT[i].targetNo);
				//		//tarid.Format("%d", TargetDetInfoT[i].targetId);
				//		//time.Format("%lf", TargetDetInfoT[i].trackTime);
				//		//x.Format("%lf", TargetDetInfoT[i].x);
				//		//y.Format("%lf", TargetDetInfoT[i].y);
				//		//z.Format("%lf", TargetDetInfoT[i].z);
				//		//vx.Format("%lf", TargetDetInfoT[i].Vx);
				//		//vy.Format("%lf", TargetDetInfoT[i].Vy);
				//		//vz.Format("%lf", TargetDetInfoT[i].Vz);
				//		//yaw.Format("%d", TargetDetInfoT[i].yaw);
				//		//pitch.Format("%d", TargetDetInfoT[i].pitch);
				//		//distance.Format("%lf", TargetDetInfoT[i].detectionDistance);
				//	}
				//	/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
				//}
				///*����������������������������������������������������������������������������������������������������������������������������������������������*/

				///*���������������������������������ڶ�����������������������������������������������������������������������������������������������������*/

				//else if (i == 1)
				//{
					if (TargetDetInfoT[i].trackTime >= 1)//ʱ�����1ʱ
					{
						memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i * sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));//��sendBuf���Ѿ�����
						//��mess��TargetInfo��
						//����֮ǰ�ĵ�ַ���ܴ���
						//��Ȼ�͸�����
						vxt[i] = cos(omiga)*vxt[i] + -sin(omiga)*vzt[i];
						vzt[i] = sin(omiga)*vxt[i] + cos(omiga)*vzt[i];


						TargetDetInfoT[i].x = TargetDetInfoT[i].x + (sin(omiga) / omiga)*vxt[i] - ((1 - cos(omiga)) / omiga)*vzt[i] / omiga;
						TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
						TargetDetInfoT[i].z = (1 - cos(omiga))*vxt[i] / omiga + TargetDetInfoT[i].z + (sin(omiga) / omiga)*vzt[i];
						TargetDetInfoT[i].trackTime++;
						TargetSence[i].push_back(TargetDetInfoT[i]);
						///////�б���ʾ
						tarno.Format("%d", TargetDetInfoT[i].targetNo);
						tarid.Format("%d", TargetDetInfoT[i].targetId);
						time.Format("%lf", TargetDetInfoT[i].trackTime);
						x.Format("%lf", TargetDetInfoT[i].x);
						y.Format("%lf", TargetDetInfoT[i].y);
						z.Format("%lf", TargetDetInfoT[i].z);
						vx.Format("%lf", TargetDetInfoT[i].Vx);
						vy.Format("%lf", TargetDetInfoT[i].Vy);
						vz.Format("%lf", TargetDetInfoT[i].Vz);
						yaw.Format("%d", TargetDetInfoT[i].yaw);
						pitch.Format("%d", TargetDetInfoT[i].pitch);
						distance.Format("%lf", TargetDetInfoT[i].detectionDistance);
					}
				}
				/*����������������������������������������������������������������������������������������������������������������������������������������������*/
				/*�����������������������������������������ߵĽ�ģ��������������������������������������������������������������������������������������������*/
				//else
				//{
				//	memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i * sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));
				//	TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
				//	TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
				//	TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
				//	TargetDetInfoT[i].trackTime++;
				//	TargetSence[i].push_back(TargetDetInfoT[i]);
				//	///////�б���ʾ
				//	tarno.Format("%d", TargetDetInfoT[i].targetNo);
				//	tarid.Format("%d", TargetDetInfoT[i].targetId);
				//	time.Format("%lf", TargetDetInfoT[i].trackTime);
				//	x.Format("%lf", TargetDetInfoT[i].x);
				//	y.Format("%lf", TargetDetInfoT[i].y);
				//	z.Format("%lf", TargetDetInfoT[i].z);
				//	vx.Format("%lf", TargetDetInfoT[i].Vx);
				//	vy.Format("%lf", TargetDetInfoT[i].Vy);
				//	vz.Format("%lf", TargetDetInfoT[i].Vz);
				//	yaw.Format("%d", TargetDetInfoT[i].yaw);
				//	pitch.Format("%d", TargetDetInfoT[i].pitch);
				//	distance.Format("%lf", TargetDetInfoT[i].detectionDistance);
				//}
				/*����������������������������������������������������������������������������������������������������������������������������������������������*/


				int Tari = m_listmuzhi.GetItemCount();
				CString TarS; TarS.Format("%d", Tari + 1);//������ʲô��
				int rownum;//�б��еĵڼ���

				/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
				for (rownum = 0; rownum < Tari; rownum++)//�����б�
				{
					CString str;
					str = m_listmuzhi.GetItemText(rownum, 0);
					if (tarno == str)//
					{
						m_listmuzhi.SetItemText(rownum, 0, tarno);
						m_listmuzhi.SetItemText(rownum, 1, tarid);
						m_listmuzhi.SetItemText(rownum, 2, time);
						m_listmuzhi.SetItemText(rownum, 3, x);
						m_listmuzhi.SetItemText(rownum, 4, y);
						m_listmuzhi.SetItemText(rownum, 5, z);
						m_listmuzhi.SetItemText(rownum, 6, vx);
						m_listmuzhi.SetItemText(rownum, 7, vy);
						m_listmuzhi.SetItemText(rownum, 8, vz);
						m_listmuzhi.SetItemText(rownum, 9, yaw);
						m_listmuzhi.SetItemText(rownum, 10, pitch);
						m_listmuzhi.SetItemText(rownum, 11, distance);
						break;
					}
				}
				/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/

				if (rownum == Tari)
				{
					m_listmuzhi.InsertItem(Tari, tarno);
					m_listmuzhi.SetItemText(Tari, 1, tarid);
					m_listmuzhi.SetItemText(Tari, 2, time);
					m_listmuzhi.SetItemText(Tari, 3, x);
					m_listmuzhi.SetItemText(Tari, 4, y);
					m_listmuzhi.SetItemText(Tari, 5, z);
					m_listmuzhi.SetItemText(Tari, 6, vx);
					m_listmuzhi.SetItemText(Tari, 7, vy);
					m_listmuzhi.SetItemText(Tari, 8, vz);
					m_listmuzhi.SetItemText(Tari, 9, yaw);
					m_listmuzhi.SetItemText(Tari, 10, pitch);
					m_listmuzhi.SetItemText(Tari, 11, distance);

					int count = m_listmuzhi.GetItemCount();
					m_listmuzhi.EnsureVisible(count - 1, false);
				}
			}
			/*��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-��-*/
		
		/************************************************************************************************************************************************/


		/************************************************************************************************************************************************/
		//if (TarNumT == 1)//����Ŀ��
		//{
		//	mess.dataLen = sizeof(TargetInfo) + 6 * sizeof(TargetDetectInfo);
		//	memcpy(sendBuf, &mess, sizeof(mess));
		//	TargetInfo.targetNumber = 6;
		//	memcpy(sendBuf + sizeof(mess), &TargetInfo, sizeof(TargetInfo));
		//	for (int i = 0; i < 6; i++)
		//	{
		//		memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i*sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));
		//		TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
		//		TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
		//		TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
		//		TargetDetInfoT[i].trackTime++;
		//		TargetSence[i].push_back(TargetDetInfoT[i]);
		//		///////�б���ʾ
		//		tarno.Format("%d", TargetDetInfoT[i].targetNo);
		//		tarid.Format("%d", TargetDetInfoT[i].targetId);
		//		time.Format("%lf", TargetDetInfoT[i].trackTime);
		//		x.Format("%lf", TargetDetInfoT[i].x);
		//		y.Format("%lf", TargetDetInfoT[i].y);
		//		z.Format("%lf", TargetDetInfoT[i].z);
		//		vx.Format("%lf", TargetDetInfoT[i].Vx);
		//		vy.Format("%lf", TargetDetInfoT[i].Vy);
		//		vz.Format("%lf", TargetDetInfoT[i].Vz);
		//		yaw.Format("%d", TargetDetInfoT[i].yaw);
		//		pitch.Format("%d", TargetDetInfoT[i].pitch);
		//		distance.Format("%lf", TargetDetInfoT[i].detectionDistance);

		//		int Tari = m_listmuzhi.GetItemCount();
		//		CString TarS; TarS.Format("%d", Tari + 1);

		//		int rownum;
		//		for (rownum = 0; rownum < Tari; rownum++)
		//		{
		//			CString str;
		//			str = m_listmuzhi.GetItemText(rownum, 0);
		//			if (tarno == str)
		//			{
		//				m_listmuzhi.SetItemText(rownum, 0, tarno);
		//				m_listmuzhi.SetItemText(rownum, 1, tarid);
		//				m_listmuzhi.SetItemText(rownum, 2, time);
		//				m_listmuzhi.SetItemText(rownum, 3, x);
		//				m_listmuzhi.SetItemText(rownum, 4, y);
		//				m_listmuzhi.SetItemText(rownum, 5, z);
		//				m_listmuzhi.SetItemText(rownum, 6, vx);
		//				m_listmuzhi.SetItemText(rownum, 7, vy);
		//				m_listmuzhi.SetItemText(rownum, 8, vz);
		//				m_listmuzhi.SetItemText(rownum, 9, yaw);
		//				m_listmuzhi.SetItemText(rownum, 10, pitch);
		//				m_listmuzhi.SetItemText(rownum, 11, distance);
		//				break;
		//			}
		//		}
		//		if (rownum == Tari)
		//		{
		//			m_listmuzhi.InsertItem(Tari, tarno);
		//			m_listmuzhi.SetItemText(Tari, 1, tarid);
		//			m_listmuzhi.SetItemText(Tari, 2, time);
		//			m_listmuzhi.SetItemText(Tari, 3, x);
		//			m_listmuzhi.SetItemText(Tari, 4, y);
		//			m_listmuzhi.SetItemText(Tari, 5, z);
		//			m_listmuzhi.SetItemText(Tari, 6, vx);
		//			m_listmuzhi.SetItemText(Tari, 7, vy);
		//			m_listmuzhi.SetItemText(Tari, 8, vz);
		//			m_listmuzhi.SetItemText(Tari, 9, yaw);
		//			m_listmuzhi.SetItemText(Tari, 10, pitch);
		//			m_listmuzhi.SetItemText(Tari, 11, distance);

		//			int count = m_listmuzhi.GetItemCount();
		//			m_listmuzhi.EnsureVisible(count - 1, false);
		//		}
		//		///////////////////////////////////////////////////////////////////////////
		//	}
		//}
		/************************************************************************************************************************************************/
		//else if (TarNumT == 2)//�˸�Ŀ��
		//{
		//	memset(sendBuf, 0, BUFSIZE);
		//	mess.dataLen = sizeof(TargetInfo) + 8 * sizeof(TargetDetectInfo);
		//	memcpy(sendBuf, &mess, sizeof(mess));
		//	TargetInfo.targetNumber = 8;
		//	memcpy(sendBuf + sizeof(mess), &TargetInfo, sizeof(TargetInfo));

		//	for (int i = 0; i < 8; i++)
		//	{
		//		memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i*sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));
		//		//if (i>=4)
		//		//{
		//		TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
		//		TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
		//		TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
		//		TargetDetInfoT[i].trackTime++;
		//		TargetSence[i].push_back(TargetDetInfoT[i]);

		//		///////�б���ʾ
		//		tarno.Format("%d", TargetDetInfoT[i].targetNo);
		//		tarid.Format("%d", TargetDetInfoT[i].targetId);
		//		time.Format("%lf", TargetDetInfoT[i].trackTime);
		//		x.Format("%lf", TargetDetInfoT[i].x);
		//		y.Format("%lf", TargetDetInfoT[i].y);
		//		z.Format("%lf", TargetDetInfoT[i].z);
		//		vx.Format("%lf", TargetDetInfoT[i].Vx);
		//		vy.Format("%lf", TargetDetInfoT[i].Vy);
		//		vz.Format("%lf", TargetDetInfoT[i].Vz);
		//		yaw.Format("%d", TargetDetInfoT[i].yaw);
		//		pitch.Format("%d", TargetDetInfoT[i].pitch);
		//		distance.Format("%lf", TargetDetInfoT[i].detectionDistance);

		//		int Tari = m_listmuzhi.GetItemCount();
		//		CString TarS; TarS.Format("%d", Tari + 1);

		//		int rownum;
		//		for (rownum = 0; rownum < Tari; rownum++)
		//		{
		//			CString str;
		//			str = m_listmuzhi.GetItemText(rownum, 0);
		//			if (tarno == str)
		//			{
		//				m_listmuzhi.SetItemText(rownum, 0, tarno);
		//				m_listmuzhi.SetItemText(rownum, 1, tarid);
		//				m_listmuzhi.SetItemText(rownum, 2, time);
		//				m_listmuzhi.SetItemText(rownum, 3, x);
		//				m_listmuzhi.SetItemText(rownum, 4, y);
		//				m_listmuzhi.SetItemText(rownum, 5, z);
		//				m_listmuzhi.SetItemText(rownum, 6, vx);
		//				m_listmuzhi.SetItemText(rownum, 7, vy);
		//				m_listmuzhi.SetItemText(rownum, 8, vz);
		//				m_listmuzhi.SetItemText(rownum, 9, yaw);
		//				m_listmuzhi.SetItemText(rownum, 10, pitch);
		//				m_listmuzhi.SetItemText(rownum, 11, distance);
		//				break;
		//			}
		//		}
		//		if (rownum == Tari)
		//		{
		//			m_listmuzhi.InsertItem(Tari, tarno);
		//			m_listmuzhi.SetItemText(Tari, 1, tarid);
		//			m_listmuzhi.SetItemText(Tari, 2, time);
		//			m_listmuzhi.SetItemText(Tari, 3, x);
		//			m_listmuzhi.SetItemText(Tari, 4, y);
		//			m_listmuzhi.SetItemText(Tari, 5, z);
		//			m_listmuzhi.SetItemText(Tari, 6, vx);
		//			m_listmuzhi.SetItemText(Tari, 7, vy);
		//			m_listmuzhi.SetItemText(Tari, 8, vz);
		//			m_listmuzhi.SetItemText(Tari, 9, yaw);
		//			m_listmuzhi.SetItemText(Tari, 10, pitch);
		//			m_listmuzhi.SetItemText(Tari, 11, distance);

		//			int count = m_listmuzhi.GetItemCount();
		//			m_listmuzhi.EnsureVisible(count - 1, false);
		//		}
		//		///////////////////////////////////////////////////////////////////////////
		//		//}
		//	}
		//}
		/************************************************************************************************************************************************/
		//else if (TarNumT == 3)
		//{
		//	memset(sendBuf, 0, BUFSIZE);
		//	mess.dataLen = sizeof(TargetInfo) + 10 * sizeof(TargetDetectInfo);
		//	memcpy(sendBuf, &mess, sizeof(mess));
		//	TargetInfo.targetNumber = 10;
		//	memcpy(sendBuf + sizeof(mess), &TargetInfo, sizeof(TargetInfo));

		//	for (int i = 0; i < 10; i++)
		//	{
		//		memcpy(sendBuf + sizeof(mess) + sizeof(TargetInfo) + i*sizeof(TargetDetectInfo), &TargetDetInfoT[i], sizeof(TargetDetectInfo));
		//		TargetDetInfoT[i].x = TargetDetInfoT[i].x + vxt[i];
		//		TargetDetInfoT[i].y = TargetDetInfoT[i].y + vyt[i];
		//		TargetDetInfoT[i].z = TargetDetInfoT[i].z + vzt[i];
		//		TargetDetInfoT[i].trackTime++;
		//		TargetSence[i].push_back(TargetDetInfoT[i]);

		//		///////�б���ʾ
		//		tarno.Format("%d", TargetDetInfoT[i].targetNo);
		//		tarid.Format("%d", TargetDetInfoT[i].targetId);
		//		time.Format("%lf", TargetDetInfoT[i].trackTime);
		//		x.Format("%lf", TargetDetInfoT[i].x);
		//		y.Format("%lf", TargetDetInfoT[i].y);
		//		z.Format("%lf", TargetDetInfoT[i].z);
		//		vx.Format("%lf", TargetDetInfoT[i].Vx);
		//		vy.Format("%lf", TargetDetInfoT[i].Vy);
		//		vz.Format("%lf", TargetDetInfoT[i].Vz);
		//		yaw.Format("%d", TargetDetInfoT[i].yaw);
		//		pitch.Format("%d", TargetDetInfoT[i].pitch);
		//		distance.Format("%lf", TargetDetInfoT[i].detectionDistance);

		//		int Tari = m_listmuzhi.GetItemCount();
		//		CString TarS; TarS.Format("%d", Tari + 1);

		//		int rownum;
		//		for (rownum = 0; rownum < Tari; rownum++)
		//		{
		//			CString str;
		//			str = m_listmuzhi.GetItemText(rownum, 0);
		//			if (tarno == str)
		//			{
		//				m_listmuzhi.SetItemText(rownum, 0, tarno);
		//				m_listmuzhi.SetItemText(rownum, 1, tarid);
		//				m_listmuzhi.SetItemText(rownum, 2, time);
		//				m_listmuzhi.SetItemText(rownum, 3, x);
		//				m_listmuzhi.SetItemText(rownum, 4, y);
		//				m_listmuzhi.SetItemText(rownum, 5, z);
		//				m_listmuzhi.SetItemText(rownum, 6, vx);
		//				m_listmuzhi.SetItemText(rownum, 7, vy);
		//				m_listmuzhi.SetItemText(rownum, 8, vz);
		//				m_listmuzhi.SetItemText(rownum, 9, yaw);
		//				m_listmuzhi.SetItemText(rownum, 10, pitch);
		//				m_listmuzhi.SetItemText(rownum, 11, distance);
		//				break;
		//			}
		//		}
		//		if (rownum == Tari)
		//		{
		//			m_listmuzhi.InsertItem(Tari, tarno);
		//			m_listmuzhi.SetItemText(Tari, 1, tarid);
		//			m_listmuzhi.SetItemText(Tari, 2, time);
		//			m_listmuzhi.SetItemText(Tari, 3, x);
		//			m_listmuzhi.SetItemText(Tari, 4, y);
		//			m_listmuzhi.SetItemText(Tari, 5, z);
		//			m_listmuzhi.SetItemText(Tari, 6, vx);
		//			m_listmuzhi.SetItemText(Tari, 7, vy);
		//			m_listmuzhi.SetItemText(Tari, 8, vz);
		//			m_listmuzhi.SetItemText(Tari, 9, yaw);
		//			m_listmuzhi.SetItemText(Tari, 10, pitch);
		//			m_listmuzhi.SetItemText(Tari, 11, distance);

		//			int count = m_listmuzhi.GetItemCount();
		//			m_listmuzhi.EnsureVisible(count - 1, false);
		//		}
		//		///////////////////////////////////////////////////////////////////////////
		//	}
		//}

		lenT = sendto(sendSocket, sendBuf, sizeof(mess) + mess.dataLen, 0, (SOCKADDR*)&saUdpServ, sizeof(SOCKADDR));

		printf("%d\n", lenT);

		break;


	case 3:
		DrawOpenGL();
		break;
	case 4:

		break;

	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CRadaDataDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cmb1flag = 1;
	cmb1index = m_tar.GetCurSel();
	TarNumT = cmb1index;
	TargetSence.resize(TarNumT+1);
	//if (cmb1index == 0)
	//	TargetSence.resize(4);
	//else if (cmb1index == 1)
	//{
	//	TargetSence.resize(6);
	//}
	//else if (cmb1index == 2)
	//{
	//	TargetSence.resize(8);
	//}
	//else if (cmb1index == 3)
	//{
	//	TargetSence.resize(10);
	//}

}


void CRadaDataDlg::OnCbnSelchangeCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int index = m_sear.GetCurSel();
	TarNumS = index;
}






void CRadaDataDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}



void CRadaDataDlg::DrawOpenGL()
{
	glClear(GL_COLOR_BUFFER_BIT);// ���������ΪԤ�ȵ�����ֵ,����ɫ

	//�򿪿���ݣ�����ʾ�����ܽ�����ѵĴ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.0);     //�����߿�

	/*****************************************************************�״�ģ��ͼ**************************************************************************************/
	//д����	
	glRasterPos2f(-0.1f, 0.9f);
	drawCNString("");
	//	selectFont(BIGFRONT, GB2312_CHARSET, "����_GB2312");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.93f, 0.93f);
	drawCNString("Ŀָ�״�");

	//�������
	double L1 = 0.015*cos(36 * PI / 180);
	double L2 = 0.015*sin(36 * PI / 180);
	double L3 = 0.015*cos(72 * PI / 180);
	double L4 = 0.015*sin(72 * PI / 180);
	double L5 = L2*tan(72 * PI / 180);
	double L6 = L2 / cos(72 * PI / 180);
	double L7 = L6*sin(54 * PI / 180);
	double L8 = L6*cos(54 * PI / 180) + 0.015;

	glColor3f(1.0, 0.0, 0.0);

	GLfloat Pi = 3.1415926f;
	GLfloat m = 0.05f;



	//��Բ��
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();

	//������˸��־
	if (shanshuo == 15)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(12.0);
		glBegin(GL_POINTS);
		glVertex2f(-0.8, 0.8);
		glEnd();
		shanshuo = 0;
	}
	shanshuo++;

	//��Բ��
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(2.0);			  //�����߿�

	float angle;
	float circle1 = 0.48;
	float circle2 = 0.32;
	float circle3 = 0.16;
	for (angle = 0.0; angle <= (2.0*PI); angle += 0.05f)
	{
		float x, y;
		x = circle1*sin(angle) * 2;
		y = circle1*cos(angle) * 2;
		glBegin(GL_LINE_LOOP);   //���պ�����
		glVertex2f(x, y);


	}
	glEnd();

	glLineWidth(1.0);
	for (angle = 0.0; angle <= (2.0*PI); angle += 0.05f)
	{
		float x, y;
		x = circle2*sin(angle) * 2;
		y = circle2*cos(angle) * 2;
		glBegin(GL_LINE_LOOP);   //���պ�����
		glVertex2f(x, y);
	}
	glEnd();

	glLineWidth(1.0);
	for (angle = 0.0; angle <= (2.0*PI); angle += 0.05f)
	{
		float x, y;
		x = circle3*sin(angle) * 2;
		y = circle3*cos(angle) * 2;
		glBegin(GL_LINE_LOOP);   //���պ�����
		glVertex2f(x, y);
	}
	glEnd();

	//�����߿̶�
	glColor3f(0.0f, 0.8f, 0.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glLineStipple(1, 0x00FF);
	for (angle = 0.0; angle <= (PI * 2); angle += PI / 6.0f)
	{
		float x, y;
		x = (circle1)*sin(angle) * 2;
		y = (circle1)*cos(angle) * 2;
		glBegin(GL_LINES);   //����
		glVertex2f(x, y);
		glVertex2f(0, 0);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);

	//��ָ����
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(0, circle1 * 2);
	glVertex2f(-0.02, circle1 * 2 + 0.04);
	glVertex2f(0.02, circle1 * 2 + 0.04);
	glEnd();

	//��ɨ��
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(circle1 * cos(dx) * 2, circle1 * sin(dx) * 2);
	glEnd();
	AfterGlo1(dx);//ɨ������
	dx -= PI / 30;


	/**********************************************************************������***************************************************************/
	glPointSize(1.0f);


	unsigned t;
	for (t = 0; t < TargetSence.size(); t++)
	{
		int j = 1;
		glColor3f(1.0, 1.0, 0);
		for (j = 0; j < TargetSence[t].size(); j++)//t��ʾ���ǵڼ���Ŀ�꣬j�Ǳ�ʾ��Ŀ��ĵڼ�����
		{

			glBegin(GL_POINTS);
			if (Hjflag == 1)
				glVertex2f(TargetSence[t][TargetSence[t].size() - 1].z / 35000.0, TargetSence[t][TargetSence[t].size() - 1].x / 35000.0);//����ʾ����
			else if (Hjflag == 0)
				glVertex2f(TargetSence[t][j].z / 35000.0, TargetSence[t][j].x / 35000.0);//��ʾ����
			glEnd();

			GLfloat ax = m;
			GLfloat bx = ax*cos(18 * Pi / 180);
			GLfloat by = ax*sin(18 * Pi / 180);
			GLfloat cx = ax*cos(54 * Pi / 180);
			GLfloat cy = -ax*sin(54 * Pi / 180);

		}
		//������
		if (j > 0)
		{
			glColor3f(1.0f, 1.0f, 1.0f); //��ɫ
			glRasterPos2f(TargetSence[t][j - 1].z*1.1 / 35000.0, TargetSence[t][j - 1].x *1.1 / 35000.0);
			if (TargetSence[t][j - 1].targetNo < 10)
			{
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 48 + TargetSence[t][j - 1].targetNo);
			}
			else
			{
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 49);
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 48 + TargetSence[t][j - 1].targetNo % 10);
			}
		}
		if (j > 0)//��Ϊǰ���и�j++
		{
			int i = j;
			for (int j = 1; j <= i; j++) {

				GLfloat PointA[2] = { 0.0f, -0.08f / 1.5 };       duichengzuobiao(PointA, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointB[2] = { 0.005f / 1.5, (0.005f - 0.08f) / 1.5 }; duichengzuobiao(PointB, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointC[2] = { 0.005f / 1.5, (0.025f - 0.08f) / 1.5 }; duichengzuobiao(PointC, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointD[2] = { 0.045f / 1.5, (0.045f - 0.08f) / 1.5 }; duichengzuobiao(PointD, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointE[2] = { 0.045f / 1.5, (0.05f - 0.08f) / 1.5 }; duichengzuobiao(PointE, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointF[2] = { 0.005f / 1.5, (0.045f - 0.08f) / 1.5 }; duichengzuobiao(PointF, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointG[2] = { 0.005f / 1.5, (0.07f - 0.08f) / 1.5 }; duichengzuobiao(PointG, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointH[2] = { 0.03f / 1.5,(0.08f - 0.08f) / 1.5 }; duichengzuobiao(PointH, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointI[2] = { 0.0f / 1.5,(0.08f - 0.08f) / 1.5 }; duichengzuobiao(PointI, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);

				GLfloat PointIN[2] = { -0.0f, 0.0f };    duichengzuobiao(PointIN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointAN[2] = { 0.0f, -0.08f / 1.5 };       duichengzuobiao(PointAN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointBN[2] = { -0.005f / 1.5, (0.005f - 0.08f) / 1.5 }; duichengzuobiao(PointBN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointCN[2] = { -0.005f / 1.5, (0.025f - 0.08f) / 1.5 }; duichengzuobiao(PointCN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointDN[2] = { -0.045f / 1.5, (0.045f - 0.08f) / 1.5 }; duichengzuobiao(PointDN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointEN[2] = { -0.045f / 1.5, (0.05f - 0.08f) / 1.5 };  duichengzuobiao(PointEN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointFN[2] = { -0.005f / 1.5, (0.045f - 0.08f) / 1.5 }; duichengzuobiao(PointFN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointGN[2] = { -0.005f / 1.5, (0.07f - 0.08f) / 1.5 };  duichengzuobiao(PointGN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				GLfloat PointHN[2] = { -0.03f / 1.5, (0.08f - 0.08f) / 1.5 };   duichengzuobiao(PointHN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				hjj = atan((hj1[t][0][1] - TargetSence[t][j - 1].x) / (hj1[t][0][0] - TargetSence[t][j - 1].z));

				if (hj1[t][0][1] - TargetSence[t][j - 1].x < 0 && hj1[t][0][0] - TargetSence[t][j - 1].z>0)
				{
					hjj = hjj + PI;
				}
				else if (hj1[t][0][1] - TargetSence[t][j - 1].x > 0 && hj1[t][0][0] - TargetSence[t][j - 1].z > 0)
				{
					hjj = hjj - PI;
				}

				hj1[t][0][0] = TargetSence[t][j - 1].z;
				hj1[t][0][1] = TargetSence[t][j - 1].x;


				//glClear(GL_COLOR_BUFFER_BIT);													  
				PointA1[j][0] = PointA[0];
				PointB1[j][0] = PointB[0];
				PointC1[j][0] = PointC[0];
				PointD1[j][0] = PointD[0];
				PointE1[j][0] = PointE[0];
				PointF1[j][0] = PointF[0];
				PointG1[j][0] = PointG[0];
				PointH1[j][0] = PointH[0];
				PointI1[j][0] = PointI[0];
				PointIN1[j][0] = PointIN[0];
				PointAN1[j][0] = PointAN[0];
				PointBN1[j][0] = PointBN[0];
				PointCN1[j][0] = PointCN[0];
				PointDN1[j][0] = PointDN[0];
				PointEN1[j][0] = PointEN[0];
				PointFN1[j][0] = PointFN[0];
				PointGN1[j][0] = PointGN[0];
				PointHN1[j][0] = PointHN[0];

				PointA1[j][1] = PointA[1];
				PointB1[j][1] = PointB[1];
				PointC1[j][1] = PointC[1];
				PointD1[j][1] = PointD[1];
				PointE1[j][1] = PointE[1];
				PointF1[j][1] = PointF[1];
				PointG1[j][1] = PointG[1];
				PointH1[j][1] = PointH[1];
				PointI1[j][1] = PointI[1];
				PointIN1[j][1] = PointIN[1];
				PointAN1[j][1] = PointAN[1];
				PointBN1[j][1] = PointBN[1];
				PointCN1[j][1] = PointCN[1];
				PointDN1[j][1] = PointDN[1];
				PointEN1[j][1] = PointEN[1];
				PointFN1[j][1] = PointFN[1];
				PointGN1[j][1] = PointGN[1];
				PointHN1[j][1] = PointHN[1];


				yidaozuobiaoyuandian(PointA, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointB, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointC, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointD, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointE, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointF, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointG, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointH, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointI, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointIN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointAN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointBN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointCN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointDN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointEN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointFN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointGN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidaozuobiaoyuandian(PointHN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);


				TransCoordinate(PointA, &R[A], &theta[A]);
				TransCoordinate(PointB, &R[B], &theta[B]);
				TransCoordinate(PointC, &R[C], &theta[C]);
				TransCoordinate(PointD, &R[D], &theta[D]);
				TransCoordinate(PointE, &R[E], &theta[E]);
				TransCoordinate(PointF, &R[F], &theta[F]);
				TransCoordinate(PointG, &R[G], &theta[G]);
				TransCoordinate(PointH, &R[H], &theta[H]);
				TransCoordinate(PointHN, &R[HN], &theta[HN]);
				TransCoordinate(PointGN, &R[GN], &theta[GN]);
				TransCoordinate(PointFN, &R[FN], &theta[FN]);
				TransCoordinate(PointEN, &R[EN], &theta[EN]);
				TransCoordinate(PointDN, &R[DN], &theta[DN]);
				TransCoordinate(PointCN, &R[CN], &theta[CN]);
				TransCoordinate(PointBN, &R[BN], &theta[BN]);
				TransCoordinate(PointAN, &R[AN], &theta[AN]);


				for (int i1 = 0; i1 <= AN; i1++)
				{
					theta[i1] = theta[i1] + hjj;
				}

				FeiJiZhuanWanHDZB(PointA, R[A], theta[A]);
				FeiJiZhuanWanHDZB(PointB, R[B], theta[B]);
				FeiJiZhuanWanHDZB(PointC, R[C], theta[C]);
				FeiJiZhuanWanHDZB(PointD, R[D], theta[D]);
				FeiJiZhuanWanHDZB(PointF, R[F], theta[F]);
				FeiJiZhuanWanHDZB(PointE, R[E], theta[E]);
				FeiJiZhuanWanHDZB(PointG, R[G], theta[G]);
				FeiJiZhuanWanHDZB(PointH, R[H], theta[H]);
				FeiJiZhuanWanHDZB(PointHN, R[HN], theta[HN]);
				FeiJiZhuanWanHDZB(PointGN, R[GN], theta[GN]);
				FeiJiZhuanWanHDZB(PointFN, R[FN], theta[FN]);
				FeiJiZhuanWanHDZB(PointEN, R[EN], theta[EN]);
				FeiJiZhuanWanHDZB(PointDN, R[DN], theta[DN]);
				FeiJiZhuanWanHDZB(PointCN, R[CN], theta[CN]);
				FeiJiZhuanWanHDZB(PointBN, R[BN], theta[BN]);
				FeiJiZhuanWanHDZB(PointAN, R[AN], theta[AN]);

				yidongfeijizuobiao(PointA, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointB, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointC, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointD, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointE, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointF, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointG, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointH, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointI, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointIN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointAN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointBN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointCN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointDN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointEN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointFN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointGN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);
				yidongfeijizuobiao(PointHN, TargetSence[t][j - 1].z / 35000.0, TargetSence[t][j - 1].x / 35000.0);

				PointA1[j][0] = PointA[0];
				PointB1[j][0] = PointB[0];
				PointC1[j][0] = PointC[0];
				PointD1[j][0] = PointD[0];
				PointE1[j][0] = PointE[0];
				PointF1[j][0] = PointF[0];
				PointG1[j][0] = PointG[0];
				PointH1[j][0] = PointH[0];
				PointI1[j][0] = PointI[0];
				PointIN1[j][0] = PointIN[0];
				PointAN1[j][0] = PointAN[0];
				PointBN1[j][0] = PointBN[0];
				PointCN1[j][0] = PointCN[0];
				PointDN1[j][0] = PointDN[0];
				PointEN1[j][0] = PointEN[0];
				PointFN1[j][0] = PointFN[0];
				PointGN1[j][0] = PointGN[0];
				PointHN1[j][0] = PointHN[0];

				PointA1[j][1] = PointA[1];
				PointB1[j][1] = PointB[1];
				PointC1[j][1] = PointC[1];
				PointD1[j][1] = PointD[1];
				PointE1[j][1] = PointE[1];
				PointF1[j][1] = PointF[1];
				PointG1[j][1] = PointG[1];
				PointH1[j][1] = PointH[1];
				PointI1[j][1] = PointI[1];
				PointIN1[j][1] = PointIN[1];
				PointAN1[j][1] = PointAN[1];
				PointBN1[j][1] = PointBN[1];
				PointCN1[j][1] = PointCN[1];
				PointDN1[j][1] = PointDN[1];
				PointEN1[j][1] = PointEN[1];
				PointFN1[j][1] = PointFN[1];
				PointGN1[j][1] = PointGN[1];
				PointHN1[j][1] = PointHN[1];

			}
		}

		if (j > 0)
		{
			int i = j;

			/****************************************���ɻ�**********************************************/
	/*	if (t%2==0)
			glColor3f(152.0 / 255, 245.0 / 255, 255.0 / 255);
		else if (t%3==0)
			glColor3f(0.0 / 255, 0xCD / 255.0, 0.0 / 255);
		else*/
		//glColor3f(255.0 / 255, 0 / 255, 0/ 255);//��
			glColor3f(152.0 / 255, 245.0 / 255, 255.0 / 255);

			/***************��ͷ*****************/
			glBegin(GL_TRIANGLES);
			glVertex2fv(PointA1[j]);
			glVertex2fv(PointB1[j]);
			glVertex2fv(PointBN1[j]);
			glEnd();
			/************************************/
			/***************����*****************/
			glBegin(GL_QUADS);
			glVertex2fv(PointB1[j]);
			glVertex2fv(PointG1[j]);
			glVertex2fv(PointGN1[j]);
			glVertex2fv(PointBN1[j]);
			glEnd();
			/***********************************/
			/***************����*****************/
			//����
			glBegin(GL_QUADS);
			glVertex2fv(PointC1[j]);
			glVertex2fv(PointD1[j]);
			glVertex2fv(PointE1[j]);
			glVertex2fv(PointF1[j]);
			glEnd();
			//����
			glBegin(GL_QUADS);
			glVertex2fv(PointCN1[j]);
			glVertex2fv(PointDN1[j]);
			glVertex2fv(PointEN1[j]);
			glVertex2fv(PointFN1[j]);
			glEnd();
			/***********************************/
			/***************��β*****************/
			glBegin(GL_QUADS);
			glVertex2fv(PointG1[j]);
			glVertex2fv(PointH1[j]);
			glVertex2fv(PointHN1[j]);
			glVertex2fv(PointGN1[j]);
			glEnd();
			/***********************************/


		}
	}

	SwapBuffers(hDC);//�л����������ͻ�������

}


void CRadaDataDlg::Reshape()
{
}


bool CRadaDataDlg::SetWindowPixelFormat(HDC hDC)
{

	static PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (m_GLPixelIndex == 0)
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}
	if (SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc) == FALSE)
	{
		return FALSE;
	}
	return TRUE;

}


bool CRadaDataDlg::CreateViewGLRC(HDC hDC)
{
	m_hGLRC = wglCreateContext(hDC);
	if (m_hGLRC == NULL)
		return FALSE;
	if (wglMakeCurrent(hDC, m_hGLRC) == FALSE)
		return FALSE;
	return TRUE;

}

UINT ChildThread(LPVOID lParam);//���߳���ڵ㺯��,�൱����һ��main,CPU��ͬʱִ��MFC�����̺߳�ChildThread�̺߳���
void CRadaDataDlg::OnBnClickedButton3()//��ʼ��ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Hjflag = 0;
	SetTimer(1, 100, NULL);//Ŀָ�״�
	SetTimer(2, 500, NULL);//�����״�
	SetTimer(3, 50, NULL);//������ʾ
	//Init();
	if (cmb1flag == 0) {
		cmb1index = 0;
		TarNumT = cmb1index;
		TargetSence.resize(TarNumT+1);
		//if (cmb1index == 0)
		//	TargetSence.resize(4);
		//else if (cmb1index == 1)
		//{
		//	TargetSence.resize(6);
		//}
		//else if (cmb1index == 2)
		//{
		//	TargetSence.resize(8);
		//}
		//else if (cmb1index == 3)
		//{
		//	TargetSence.resize(10);
		//}
	}
	//����Ŀ�������Ϣ
	if (ThreadFlag)
	{
		ThreadFlag = FALSE;
		//	GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("���շ�����Ϣ"));
		return;
	}
	else
	{
		ThreadFlag = TRUE;
		HANDLE hMultiThread = AfxBeginThread(ChildThread, /*(LPVOID)*/this, THREAD_PRIORITY_IDLE);//ChildThread�̺߳������
	//	GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("ֹͣ���շ�����Ϣ"));
		return;
	}


}



UINT ChildThread(LPVOID lParam)//���߳���ڵ㺯��,�൱����һ��main,CPU��ͬʱִ��MFC�����̺߳�ChildThread�̺߳���
{

	CRadaDataDlg* pDlg = (CRadaDataDlg*)lParam;//����һ��ָ�����Ի���ľ��

	CString str;

	int ThreadCound = 1;

	SOCKADDR_IN sin, saClient;                          //����������ַ��sin������
	//saClient�����ӹ㲥��ַ������Ϣ

	int nSize;


	if (recvSocket == INVALID_SOCKET) {
		recvSocket = socket(AF_INET, SOCK_DGRAM, 0);//(PF_INET, SOCK_DGRAM
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(3000);             //���Ͷ�ʹ�õķ��Ͷ˿ڣ����Ը�����Ҫ����
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	BOOL isReuseAddr = TRUE;                             //����setsockopt(),��ʾ����
	setsockopt(recvSocket, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&isReuseAddr, sizeof(BOOL));

	if (bind(recvSocket, (SOCKADDR FAR *)&sin, sizeof(sin)) != 0)
	{
		printf("Can't bind socket to local port!Program stop.\n");
	}
	nSize = sizeof(SOCKADDR_IN);
	char recvBuf1[BUFSIZ];
	int len1 = sizeof(SOCKADDR);//sizeof(SOCKADDR_IN); 

	MessageHeader mess;
	TargetAssignmentInfo TarAssInfo;
	AssTargetInfo AssInfo;
	CString fireid, tarnum, tarno, tarid, thread, x, y, z, vx, vy, vz;

	while (pDlg->ThreadFlag)
	{

		// str.Format(_T("���߳̿�����%d��"), ThreadCound++);//	    
		// pDlg->GetDlgItem(IDC_RECV)->SetWindowText(str);//�����ӶԻ�����ʾstr�����ݣ�pDlgָ�����Ի�������ڵ㡣�༭��Ͱ�ť�ؼ��������Ի����ϣ����Կ���ͨ����ȡ���Ի������ϵľ�������ú��޸����Ի����ϰ�ť�ؼ���ͱ༭���ࡣIDC_EDIT_CHILD���̱߳༭���ID����Ҫ�޸�Ϊ�Լ��ӶԻ���ID��
		std::memset(recvBuf1, 0, BUFSIZ);
		int retval1 = recvfrom(recvSocket, recvBuf1, sizeof(recvBuf1), 0, (SOCKADDR*)&saClient, &len1);
		memcpy(&mess, recvBuf1, sizeof(mess));
		if (mess.childDataType == 16)
		{
			memcpy(&TarAssInfo, recvBuf1 + sizeof(mess), sizeof(TarAssInfo));
			memcpy(&AssInfo, recvBuf1 + sizeof(mess) + sizeof(TarAssInfo), sizeof(AssInfo));
			fireid.Format("%d", TarAssInfo.fireID);
			tarnum.Format("%d", TarAssInfo.targetNumber);
			tarno.Format("%d", AssInfo.targetNo);
			tarid.Format("%d", AssInfo.targetId);
			thread.Format("%d", AssInfo.threatLevel);
			x.Format("%lf", AssInfo.x);
			y.Format("%lf", AssInfo.y);
			z.Format("%lf", AssInfo.z);
			vx.Format("%lf", AssInfo.Vx);
			vy.Format("%lf", AssInfo.Vy);
			vz.Format("%lf", AssInfo.Vz);


		}

		//  Sleep(1000);//��ʱ1����

	}

	return 0;

}



void CRadaDataDlg::AfterGlo1(double dx)//ɨ������
{
	float q = 0.48*cos(dx) * 2;
	float p = 0.48*sin(dx) * 2;
	float color = 0.6f;
	for (int i = 0; i < 15; i++)
	{

		float q1 = (0.48)*cos(dx) * 2;
		float p1 = (0.48)*sin(dx) * 2;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);       ////////������������͸���ȣ���������������������

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, color, 0.0f);
		glVertex2f(q1, p1);
		glColor3f(0.0f, color, 0.0f);
		glVertex2f(0, 0);
		glColor3f(0.0f, color, 0.0f);
		glVertex2f(q, p);
		glEnd();
		dx = dx + 0.1;
		q = q1;
		p = p1;
		color -= 0.05;
		glDisable(GL_BLEND);
	}
}


void CRadaDataDlg::drawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	//�����ַ��ĸ���
	//�����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	//����һ���ֽ���һ���ַ�
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	//������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	//�������ַ�
	for (i = 0; i < len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	//����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}





void CRadaDataDlg::TransCoordinate(GLfloat *ZuoBiao, GLfloat *Radius, GLfloat *JioaDu)
{
	*Radius = sqrt(ZuoBiao[0] * ZuoBiao[0] + ZuoBiao[1] * ZuoBiao[1]);
	*JioaDu = atan(ZuoBiao[1] / ZuoBiao[0]);

}

void CRadaDataDlg::FeiJiZhuanWanHDZB(GLfloat *ZuoBiao, GLfloat Radius, GLfloat JiaoDu)
{
	ZuoBiao[0] = Radius*cos(JiaoDu);
	ZuoBiao[1] = Radius*sin(JiaoDu);
}

void CRadaDataDlg::duichengzuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x)//�ѷɻ���ɺ��
{
	GLfloat temp;
	temp = ZuoBiao[0];
	ZuoBiao[0] = -ZuoBiao[1] + z;
	ZuoBiao[1] = -temp + x;
}

void CRadaDataDlg::yidaozuobiaoyuandian(GLfloat *ZuoBiao, GLfloat z, GLfloat x)
{
	ZuoBiao[0] = ZuoBiao[0] - z;
	ZuoBiao[1] = ZuoBiao[1] - x;
}

void CRadaDataDlg::yidongfeijizuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x)
{
	ZuoBiao[0] = ZuoBiao[0] + z;
	ZuoBiao[1] = ZuoBiao[1] + x;
}

void CRadaDataDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Hjflag = 0;
}

void CRadaDataDlg::OnBnClickedTuichu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (Hjflag == 0)
		Hjflag = 1;
}


void CRadaDataDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Hjflag = 1;
}



HBRUSH CRadaDataDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)//ע��˴��ģ�pWnd->��������ûЧ��/*nCtlColor == CTLCOLOR_EDIT &&*/
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(79, 79, 79));
		//pDC->SetBkColor(RGB(255, 255, 255));//�����ı�����ɫ
		pDC->SetBkMode(OPAQUE);//���ñ���͸��
		return(HBRUSH)GetStockObject(NULL_BRUSH);
		/*hbr = (HBRUSH)m_brush;*/
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


