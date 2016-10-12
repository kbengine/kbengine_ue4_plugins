// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"


/*
初始化KBEngine的参数类
*/
class KBENGINEPLUGINS_API KBEngineArgs
{
public:
	KBEngineArgs();
	virtual ~KBEngineArgs();

public:
	FString ip;
	int port;

	// 客户端类型
	// Reference: http://www.kbengine.org/docs/programming/clientsdkprogramming.html, client types
	EKCLIENT_TYPE clientType;

	bool syncPlayer;
	bool useAliasEntityID;
	bool isOnInitCallPropertysSetMethods;
};
