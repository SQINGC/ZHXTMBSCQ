
// RadaDataDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<gl/GL.h>
#include<GLAUX.H>
#include<vector>
//#include "analyPrototol.h"
#include"networkDialog.h"

#define  NUM 15
// CRadaDataDlg �Ի���
class CRadaDataDlg : public CDialogEx
{
	// ����
public:
	CRadaDataDlg(CWnd* pParent = NULL);	// ��׼���캯��

	~CRadaDataDlg();

	// �Ի�������
	enum { IDD = IDD_RADADATA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	SOCKET sendSocket;//�����׽���
	CComboBox m_tar;
	CComboBox m_sear;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();

	void  selectFont(int size, int charset, const char* face);

	afx_msg void OnBnClickedCancel();
	int m_GLPixelIndex;
	HDC hDC;
	void DrawOpenGL();
	void Reshape();
	bool SetWindowPixelFormat(HDC hDC);
	bool CreateViewGLRC(HDC hDC);
	HGLRC m_hGLRC;
	afx_msg void OnBnClickedButton3();

	enum motionType
	{
		yuanzhou,
		zhixian
	};
	int motionType;
	int motionSelect;


public:
	int cmb1index;//comobox1������
	int cmb1flag;//comobox1�ı�־
	int ThreadFlag;//�߳̿����͹رձ�־

	short DamageID;//Ŀ�����ID
	std::vector<int>damage_ID;//�洢����Ŀ��ID
	std::vector<short>damageV;//����Ŀ��id�洢
	std::vector<bool>isDamaged;//�Ƿ�Ϊ����Ŀ��

	CListCtrl m_listmuzhi;
	//void AfterGlo();
	void AfterGlo1(double dx);
	void drawCNString(const char* str);
	CBrush m_Brush;//������ˢ

	bool canStart;//�ܷ������棿
	bool sendRecv;//���������շ���־


	int planeflag;//������ʾ�ɻ���־

	GLfloat  xrot;   // X ��ת��
	GLfloat  yrot;   // Y ��ת��
	GLfloat  zrot;   // Z ��ת��
	GLfloat xRot = 0.0f;
	GLfloat yRot = 0.0f;

	GLfloat PointA1[NUM][2];  //�洢ת���ɻ��ĵ������
	GLfloat PointB1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointC1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointD1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointE1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointF1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointG1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointH1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointI1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointIN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointAN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointBN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointCN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointDN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointEN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointFN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointGN1[NUM][2]; //�洢ת���ɻ��ĵ������
	GLfloat PointHN1[NUM][2]; //�洢ת���ɻ��ĵ������

	GLfloat R[NUM], theta[NUM];//�洢������ֵ
	GLfloat beta[NUM];//�ɻ�ת��
	GLfloat hjr[NUM], hjj;//�洢������ļ�����ֵ
	GLfloat hj1[20][20][2];//�洢��һ�������������ֵ

	int Hjflag;//�Ƿ���ʾ����

	void TransCoordinate(GLfloat *ZuoBiao, GLfloat *Radius, GLfloat *JioaDu);//ֱ�������뼫�����ת��

	void FeiJiZhuanWanHDZB(GLfloat *ZuoBiao, GLfloat Radius, GLfloat JiaoDu);//�ɻ�ת�����ԭ�������
	void duichengzuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//�ѷɻ��������Ƶ���Ӧ��λ��
	void yidaozuobiaoyuandian(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//�ѷɻ��Ƶ�����ԭ��
	void yidongfeijizuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//�ѷɻ��ƶ�����Ӧ��λ��
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedTuichu();
	afx_msg void OnBnClickedButton5();
	//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	// �����ٶ�
	CString m_simvelo;
public:
	CComboBox com_v;
	int v_lv;//�ٶȵȼ�
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	// ��־��
//	CEdit RecvTemp;
};

//BOOL LoadTextureGL(char *Filename, GLuint &texture);