// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.



#pragma once

#include "KBVar.h"
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

/*
	用于在需要创建某个实体时被插件底层调用创建。
	每添加一个新的实体必须在源代码中加入宏 KBENGINE_ENTITY_CLASS_REGISTER(XEntity)，以便底层注册一个相关的EntityCreator
*/
class KBENGINEPLUGINS_API EntityCreator
{
public:
	EntityCreator(const FString& scriptName);

	virtual ~EntityCreator();

	virtual Entity* create() = 0;
};

/*
	实体创建工厂类
*/
class KBENGINEPLUGINS_API EntityFactory
{
public:
	static Entity* create(const FString& scriptName);
	EntityCreator* addEntityCreator(const FString& scriptName, EntityCreator* pEntityCreator);

	static EntityCreator* findCreator(const FString& scriptName);

	TMap<FString, EntityCreator*> creators;
};

/*
	包装实体的set_*方法
*/
class KBENGINEPLUGINS_API EntityDefMethodHandle
{
public:
	EntityDefMethodHandle(const FString& scriptName, const FString& defMethodName);

	virtual ~EntityDefMethodHandle();

	virtual void callMethod(Entity* pEntity, KBVar* oldVal) = 0;
};

class KBENGINEPLUGINS_API EntityDefMethodHandles
{
public:
	EntityDefMethodHandle* add(const FString& scriptName, const FString& defMethodName, EntityDefMethodHandle* pEntityDefMethodHandle);
	static EntityDefMethodHandle* find(const FString& scriptName, const FString& defMethodName);

	TMap<FString, TMap<FString, EntityDefMethodHandle*>> defMethodHandles;
};

#define ENTITY_CLASS_REGISTER(ENTITY_SCRIPTMODULE_NAME)	\
	class ENTITY_SCRIPTMODULE_NAME##Creator : public EntityCreator {	\
		public:	\
			ENTITY_SCRIPTMODULE_NAME##Creator(const FString& scriptName):	\
			EntityCreator(scriptName)	\
			{	\
			}	\
			virtual ~ENTITY_SCRIPTMODULE_NAME##Creator()	\
			{	\
			}	\
			virtual Entity* create() override	\
			{	\
				return new ENTITY_SCRIPTMODULE_NAME();	\
			}	\
	};\
	ENTITY_SCRIPTMODULE_NAME##Creator g_ENTITY_SCRIPTMODULE_NAME##Creator(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)));	\


#define ENTITY_DEFMETHOD_REGISTER(ENTITY_SCRIPTMODULE_NAME, DEF_METHOD_NAME)	\
	class ENTITY_SCRIPTMODULE_NAME##DefMethodHandle : public EntityDefMethodHandle {	\
		public:	\
			ENTITY_SCRIPTMODULE_NAME##DefMethodHandle(const FString& scriptName, const FString& defMethodName):	\
			EntityDefMethodHandle(scriptName, defMethodName)	\
			{	\
			}	\
			virtual ~ENTITY_SCRIPTMODULE_NAME##DefMethodHandle()	\
			{	\
			}	\
			virtual void callMethod(Entity* pEntity, KBVar* oldVal) override	\
			{	\
				static_cast<ENTITY_SCRIPTMODULE_NAME*>(pEntity)->DEF_METHOD_NAME(*oldVal);	\
			}	\
	};\
	ENTITY_SCRIPTMODULE_NAME##DefMethodHandle g_ENTITY_SCRIPTMODULE_NAME##DefMethodHandle(FString(TEXT(#ENTITY_SCRIPTMODULE_NAME)), FString(TEXT(#DEF_METHOD_NAME)));	\








