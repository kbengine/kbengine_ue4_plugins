// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

/*
消息模块
客户端与服务端交互基于消息通讯， 任何一个行为一条指令都是以一个消息包来描述
*/
class KBENGINEPLUGINS_API Message
{
public:
	Message(MessageID mid, const FString& mname, int16 mmsglen, uint8 margsType);
	virtual ~Message();

public:
	static Message* getMessage(const FString& messageName);
	static void setMessage(const FString& messageName, Message* pMessage);

	static void clear();
	static void bindFixedMessage();

public:
	MessageID id;
	FString name;
	int16 msglen;
	//public System.Reflection.MethodInfo handler = null;
	//public KBEDATATYPE_BASE[] argtypes = null;
	uint8 argsType;

	static TMap<MessageID, Message*> loginappMessages;
	static TMap<MessageID, Message*> baseappMessages;
	static TMap<MessageID, Message*> clientMessages;

	static TMap<FString, Message*> messages;
};
