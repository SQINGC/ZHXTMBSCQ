#include "stdafx.h"
#include "analyPrototol.h"
#include <string>

using namespace std;
AnalyPrototol::AnalyPrototol()
{
}

AnalyPrototol::~AnalyPrototol()
{
}

MessageHeader AnalyPrototol::getMsgHeader(char* msg)
{
	// 消息的前四个字节是消息类型
	MessageHeader msgheader;
	int size = sizeof(MessageHeader);
	memset(&msgheader, 0, size);
	memcpy(&msgheader, msg, sizeof(MessageHeader));
	return msgheader;
}

void AnalyPrototol::getMsgContent(char* msg, char* content, int dataLen)
{
	int headLen = sizeof(MessageHeader);
	memcpy(content, msg + headLen, dataLen);
}

//CStringArray DivString(CString test,char c)
//{
//	CStringArray m_result;
//	CString s(c);
//	while (TRUE)
//	{
//		int index = test.Find(s);
//		if (index == -1)
//		{
//			m_result.Add(test);
//			return m_result;
//		}
//		CString test1 = test.Left(index);
//		m_result.Add(test1);
//		test = test.Right(test.GetLength() - index - 1);
//	}
//
//}


