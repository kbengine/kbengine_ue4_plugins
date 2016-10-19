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
	Message();
	virtual ~Message();

public:
	

public:
	MessageID id;
	FString name;
	int16 msglen;
	//public System.Reflection.MethodInfo handler = null;
	//public KBEDATATYPE_BASE[] argtypes = null;
	uint8 argsType;
};
