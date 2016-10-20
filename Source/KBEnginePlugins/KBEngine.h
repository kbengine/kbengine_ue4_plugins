// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

class KBEngineArgs;
class Entity;
class NetworkInterface;
class MemoryStream;

/*
这是KBEngine插件的核心模块
包括网络创建、持久化协议、entities的管理、以及引起对外可调用接口。

一些可以参考的地方:
http://www.kbengine.org/docs/programming/clientsdkprogramming.html
http://www.kbengine.org/docs/programming/kbe_message_format.html

http://www.kbengine.org/cn/docs/programming/clientsdkprogramming.html
http://www.kbengine.org/cn/docs/programming/kbe_message_format.html
*/
class KBENGINEPLUGINS_API KBEngineApp : public InterfaceLogin
{
public:
	KBEngineApp();
	KBEngineApp(KBEngineArgs* pArgs);
	virtual ~KBEngineApp();
	
public:
	bool initialize(KBEngineArgs* pArgs);
	void destroy();
	void reset();

	NetworkInterface* pNetworkInterface() const {
		return pNetworkInterface_;
	}

	KBEngineArgs* getInitArgs() const
	{
		return pArgs_;
	}

	void resetMessages();

	/**
		插件的主循环处理函数
	*/
	void process();

	/*
		向服务端发送心跳以及同步角色信息到服务端
	*/
	void sendTick();

	/**
		登录到服务端，必须登录完成loginapp与网关(baseapp)，登录流程才算完毕
	*/
	bool login(FString& username, FString& password, TArray<uint8>& datas);
	virtual void onLoginCallback(FString ip, uint16 port, bool success, int userdata) override;

private:
	bool initNetwork();

	void hello();
	void Client_onHelloCB(MemoryStream& stream);

	void login_loginapp(bool noconnect);
	void onConnectTo_loginapp_callback(FString ip, uint16 port, bool success);
	void onLogin_loginapp();

	void login_baseapp(bool noconnect);
	void onConnectTo_baseapp_callback(FString ip, uint16 port, bool success);
	void onLogin_baseapp();


	void clearSpace(bool isall);
	void clearEntities(bool isall);


	void updatePlayerToServer();

	void onServerDigest();

protected:
	KBEngineArgs* pArgs_;
	NetworkInterface* pNetworkInterface_;

	FString username_;
	FString password_;

	// 是否正在加载本地消息协议
	static bool loadingLocalMessages_;

	// 消息协议是否已经导入了
	static bool loginappMessageImported_;
	static bool baseappMessageImported_;
	static bool entitydefImported_;
	static bool isImportServerErrorsDescr_;

	// 服务端分配的baseapp地址
	FString baseappIP_;
	uint16 baseappPort_;

	// 当前状态
	FString currserver_;
	FString currstate_;

	// 服务端下行以及客户端上行用于登录时处理的账号绑定的二进制信息
	// 该信息由用户自己进行扩展
	TArray<uint8> serverdatas_;
	TArray<uint8> clientdatas_;

	// 通信协议加密，blowfish协议
	TArray<uint8> encryptedKey_;

	// 服务端与客户端的版本号以及协议MD5
	FString serverVersion_;
	FString clientVersion_;
	FString serverScriptVersion_;
	FString clientScriptVersion_;
	FString serverProtocolMD5_;
	FString serverEntitydefMD5_;

	// 当前玩家的实体id与实体类别
	uint64 entity_uuid_;
	int32 entity_id_;
	FString entity_type_;

	// space的数据，具体看API手册关于spaceData
	// https://github.com/kbengine/kbengine/tree/master/docs/api
	TMap<FString, FString> spacedatas_;
	
	// 所有实体都保存于这里， 请参看API手册关于entities部分
	// https://github.com/kbengine/kbengine/tree/master/docs/api
	TMap<int32, Entity*> entities_;

	// 所有服务端错误码对应的错误描述
	static TMap<uint16, FKServerErr> serverErrs_;

	double lastTickTime_;
	double lastTickCBTime_;
	double lastUpdateToServerTime_;

	// 玩家当前所在空间的id， 以及空间对应的资源
	uint32 spaceID_;
	FString spaceResPath_;
	bool isLoadedGeometry_;

	// 按照标准，每个客户端部分都应该包含这个属性
	FString component_;

};
