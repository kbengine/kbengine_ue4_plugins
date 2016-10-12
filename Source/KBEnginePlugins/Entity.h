// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

class Mailbox;

/*
KBEngine逻辑层的实体基础类
所有扩展出的游戏实体都应该继承于该模块
*/
class KBENGINEPLUGINS_API Entity
{
public:
	Entity();
	virtual ~Entity();

public:
	

protected:
	int32 id_;
	FString className_;

	FVector position_;
	FVector direction_;

	bool isOnGround_;

	Mailbox* base_;
	Mailbox* cell_;

	bool inited_;
};
