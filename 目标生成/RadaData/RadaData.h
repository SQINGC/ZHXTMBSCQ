
// RadaData.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRadaDataApp: 
// �йش����ʵ�֣������ RadaData.cpp
//

class CRadaDataApp : public CWinApp
{
public:
	CRadaDataApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRadaDataApp theApp;