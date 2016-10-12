// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

class NetworkInterface;

/*
	包接收模块(与服务端网络部分的名称对应)
	处理网络数据的接收
*/
class KBENGINEPLUGINS_API PacketReceiver
{
public:
	PacketReceiver(NetworkInterface* pNetworkInterface);
	virtual ~PacketReceiver();

public:
	void process();

protected:
	NetworkInterface* pNetworkInterface_;
};
