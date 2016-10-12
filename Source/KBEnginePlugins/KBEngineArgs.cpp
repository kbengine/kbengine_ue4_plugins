
#include "KBEnginePluginsPrivatePCH.h"
#include "KBEngineArgs.h"

KBEngineArgs::KBEngineArgs():
	ip("127.0.0.1"),
	port(20013),
	clientType(EKCLIENT_TYPE::CLIENT_TYPE_WIN),
	syncPlayer(true),
	useAliasEntityID(true),
	isOnInitCallPropertysSetMethods(true)
{
}

KBEngineArgs::~KBEngineArgs()
{
}
