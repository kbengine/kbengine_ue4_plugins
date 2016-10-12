
#include "KBEnginePluginsPrivatePCH.h"
#include "PacketSender.h"

PacketSender::PacketSender(NetworkInterface* pNetworkInterface) :
	pNetworkInterface_(pNetworkInterface)
{
}

PacketSender::~PacketSender()
{
}


bool PacketSender::send(FString datas)
{
	FString serialized = TEXT("loadPlayer|1");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;

	return pNetworkInterface_->socket()->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}