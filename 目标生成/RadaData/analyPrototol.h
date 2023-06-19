// ����ͷ
#pragma once
#pragma pack(1)
#include "initialDataType1.h"
#include "typeDefine.h"

//struct MessageHeader {
//	char	dataType;		        // ��������
//	short	nodeID;		            // �ڵ�ID
//	int		sourceID;		        // ���ͷ�ID
//	char	childDataType;			// ��������
//	int		dataLen;		        // ���������ֽڳ���
//	int		serialNumber;	        // ������ˮ��
//	double	time;			        // ʱ���
//	char	version;		        // �汾��
//};


class AnalyPrototol
{
public:
	AnalyPrototol(void);
	~AnalyPrototol(void);

	// ��ȡ����ͷ
	static MessageHeader getMsgHeader(char* msg);

	// ��ȡ��Ϣ����
	static void getMsgContent(char* msg, char* content, int dataLen);

	// �齨��Ϣͷ????
	static void createMsgHeader(char dataType, short nodeID, short sourceID,
		char childDataType, int dataLen, int serialNumber, double time, char version,
		CString* msgByte = nullptr);

	//bool AnalyMess(char* msg, char* content, CommCar &msgcontent, int datalen);
};