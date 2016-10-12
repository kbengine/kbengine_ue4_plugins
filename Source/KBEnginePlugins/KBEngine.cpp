
#include "KBEnginePluginsPrivatePCH.h"
#include "KBEngine.h"
#include "KBEngineArgs.h"
#include "Entity.h"
#include "NetworkInterface.h"

KBEngineApp::KBEngineApp() :
	pArgs_(NULL),
	pNetworkInterface_(NULL),
	username_(""),
	password_(""),
	baseappIP_(""),
	baseappPort_(0),
	serverdatas_(""),
	clientdatas_(""),
	encryptedKey_(""),
	serverVersion_(""),
	clientVersion_(""),
	serverScriptVersion_(""),
	clientScriptVersion_(""),
	serverProtocolMD5_(""),
	serverEntitydefMD5_(""),
	entity_uuid_(0),
	entity_id_(0),
	entity_type_(""),
	spacedatas_(),
	entities_(),
	serverErrs_(),
	spaceID_(0),
	spaceResPath_(""),
	isLoadedGeometry_(false),
	component_("client")
{
	TRACE("hello!");
}

KBEngineApp::KBEngineApp(KBEngineArgs* pArgs):
	pArgs_(NULL),
	pNetworkInterface_(NULL),
	username_(""),
	password_(""),
	baseappIP_(""),
	baseappPort_(0),
	serverdatas_(""),
	clientdatas_(""),
	encryptedKey_(""),
	serverVersion_(""),
	clientVersion_(""),
	serverScriptVersion_(""),
	clientScriptVersion_(""),
	serverProtocolMD5_(""),
	serverEntitydefMD5_(""),
	entity_uuid_(0),
	entity_id_(0),
	entity_type_(""),
	spacedatas_(),
	entities_(),
	serverErrs_(),
	spaceID_(0),
	spaceResPath_(""),
	isLoadedGeometry_(false),
	component_("client")
{
	TRACE("hello!");
	initialize(pArgs);
}

KBEngineApp::~KBEngineApp()
{
	destroy();
	TRACE("destructed!");
}

bool KBEngineApp::initialize(KBEngineArgs* pArgs)
{
	reset();

	pArgs_ = pArgs;

	return initNetwork();
}

void KBEngineApp::destroy()
{
	reset();
}

void KBEngineApp::reset()
{
	username_ = "kbengine";
	password_ = "123456";

	baseappIP_ = "";
	baseappPort_ = 0;

	serverdatas_ = "";

	serverVersion_ = "";
	clientVersion_ = "0.9.0";
	serverScriptVersion_ = "";
	clientScriptVersion_ = "0.1.0";
	serverProtocolMD5_ = "";
	serverEntitydefMD5_ = "";

	entity_uuid_ = 0;
	entity_id_ = 0;
	entity_type_ = "";

	spaceID_ = 0;
	spaceResPath_ = "";
	isLoadedGeometry_ = false;

	component_ = "client";

	if (pNetworkInterface_)
	{
		delete pNetworkInterface_;
		pNetworkInterface_ = NULL;
	}

	if (pArgs_)
	{
		delete pArgs_;
		pArgs_ = NULL;
	}
}

bool KBEngineApp::initNetwork()
{
	if (pNetworkInterface_)
		delete pNetworkInterface_;

	pNetworkInterface_ = new NetworkInterface();
	return true;
}

void KBEngineApp::process()
{
	// 处理网络
	if (pNetworkInterface_)
		pNetworkInterface_->process();

	// 向服务端发送心跳以及同步角色信息到服务端
	sendTick();
}

void KBEngineApp::sendTick()
{
	if (!pNetworkInterface_ || !pNetworkInterface_->valid())
		return;
}

bool KBEngineApp::login(FString username, FString password, FString datas)
{
	username_ = username;
	password_ = password;
	clientdatas_ = datas;

	return pNetworkInterface_->connectTo(pArgs_->ip, pArgs_->port);
}