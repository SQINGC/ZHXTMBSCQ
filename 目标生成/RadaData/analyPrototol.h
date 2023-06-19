// 报文头
#pragma once
#pragma pack(1)
#include "initialDataType1.h"
#include "typeDefine.h"

//struct MessageHeader {
//	char	dataType;		        // 数据类型
//	short	nodeID;		            // 节点ID
//	int		sourceID;		        // 发送方ID
//	char	childDataType;			// 数据类型
//	int		dataLen;		        // 数据正文字节长度
//	int		serialNumber;	        // 报文流水号
//	double	time;			        // 时间戳
//	char	version;		        // 版本号
//};


class AnalyPrototol
{
public:
	AnalyPrototol(void);
	~AnalyPrototol(void);

	// 获取报文头
	static MessageHeader getMsgHeader(char* msg);

	// 获取消息内容
	static void getMsgContent(char* msg, char* content, int dataLen);

	// 组建消息头????
	static void createMsgHeader(char dataType, short nodeID, short sourceID,
		char childDataType, int dataLen, int serialNumber, double time, char version,
		CString* msgByte = nullptr);

	//bool AnalyMess(char* msg, char* content, CommCar &msgcontent, int datalen);
};