
// RadaDataDlg.h : 头文件
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
// CRadaDataDlg 对话框
class CRadaDataDlg : public CDialogEx
{
	// 构造
public:
	CRadaDataDlg(CWnd* pParent = NULL);	// 标准构造函数

	~CRadaDataDlg();

	// 对话框数据
	enum { IDD = IDD_RADADATA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	SOCKET sendSocket;//创建套接字
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
	int cmb1index;//comobox1的索引
	int cmb1flag;//comobox1的标志
	int ThreadFlag;//线程开启和关闭标志

	short DamageID;//目标毁伤ID
	std::vector<int>damage_ID;//存储毁伤目标ID
	std::vector<short>damageV;//毁伤目标id存储
	std::vector<bool>isDamaged;//是否为毁伤目标

	CListCtrl m_listmuzhi;
	//void AfterGlo();
	void AfterGlo1(double dx);
	void drawCNString(const char* str);
	CBrush m_Brush;//声明画刷

	bool canStart;//能否开启仿真？
	bool sendRecv;//允许数据收发标志


	int planeflag;//开启显示飞机标志

	GLfloat  xrot;   // X 旋转量
	GLfloat  yrot;   // Y 旋转量
	GLfloat  zrot;   // Z 旋转量
	GLfloat xRot = 0.0f;
	GLfloat yRot = 0.0f;

	GLfloat PointA1[NUM][2];  //存储转弯后飞机的点的坐标
	GLfloat PointB1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointC1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointD1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointE1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointF1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointG1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointH1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointI1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointIN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointAN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointBN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointCN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointDN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointEN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointFN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointGN1[NUM][2]; //存储转弯后飞机的点的坐标
	GLfloat PointHN1[NUM][2]; //存储转弯后飞机的点的坐标

	GLfloat R[NUM], theta[NUM];//存储极坐标值
	GLfloat beta[NUM];//飞机转角
	GLfloat hjr[NUM], hjj;//存储航迹点的极坐标值
	GLfloat hj1[20][20][2];//存储上一个航迹点的坐标值

	int Hjflag;//是否显示航迹

	void TransCoordinate(GLfloat *ZuoBiao, GLfloat *Radius, GLfloat *JioaDu);//直角坐标与极坐标的转换

	void FeiJiZhuanWanHDZB(GLfloat *ZuoBiao, GLfloat Radius, GLfloat JiaoDu);//飞机转弯后在原点的坐标
	void duichengzuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//把飞机倒过来移到相应的位置
	void yidaozuobiaoyuandian(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//把飞机移到坐标原点
	void yidongfeijizuobiao(GLfloat *ZuoBiao, GLfloat z, GLfloat x);//把飞机移动到相应的位置
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedTuichu();
	afx_msg void OnBnClickedButton5();
	//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	// 仿真速度
	CString m_simvelo;
public:
	CComboBox com_v;
	int v_lv;//速度等级
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	// 日志框
//	CEdit RecvTemp;
};

//BOOL LoadTextureGL(char *Filename, GLuint &texture);