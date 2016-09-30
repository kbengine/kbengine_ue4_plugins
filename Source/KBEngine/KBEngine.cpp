
#include "KBEnginePluginsPrivatePCH.h"
#include "KBEngine.h"
#include "KBEngineArgs.h"
#include "Entity.h"

KBEngineApp::KBEngineApp()
{
	username = "kbengine";
	password = "123456";

	baseappIP = "";
	baseappPort = 0;

	serverVersion = "";
	clientVersion = "0.9.0";
	serverScriptVersion = "";
	clientScriptVersion = "0.1.0";
	serverProtocolMD5 = "";
	serverEntitydefMD5 = "";

	entity_uuid = 0;
	entity_id = 0;
	entity_type = "";

	spaceID = 0;
	spaceResPath = "";
	isLoadedGeometry = false;

	component = "client";

	pArgs = new KBEngineArgs();
}

KBEngineApp::~KBEngineApp()
{
}
