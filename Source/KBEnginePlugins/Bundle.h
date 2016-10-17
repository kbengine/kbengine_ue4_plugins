// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

class MemoryStream;
class NetworkInterface;
class Message;

/*
	这个模块将多个数据包打捆在一起
	由于每个数据包都有最大上限， 向Bundle中写入大量数据将会在内部产生多个MemoryStream
	在send时会全部发送出去
*/
class KBENGINEPLUGINS_API Bundle
{
public:
	Bundle();
	virtual ~Bundle();

public:
	static Bundle* createObject();
	static void reclaimObject(Bundle* obj);

	void newMessage(Message* pMsg);
	void fini(bool issend);

	void writeMsgLength();
	void send(NetworkInterface* pNetworkInterface);

	void checkStream(uint32 v);

public:

protected:
	MemoryStream* pCurrStream_;
	TArray<MemoryStream*> streams_;

	int numMessage_;
	int messageLength_;
	Message* pMsgtype_;
	int curMsgStreamIndex_;
};
