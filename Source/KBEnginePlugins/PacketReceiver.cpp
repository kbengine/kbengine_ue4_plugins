
#include "KBEnginePluginsPrivatePCH.h"
#include "PacketReceiver.h"
#include "NetworkInterface.h"

PacketReceiver::PacketReceiver(NetworkInterface* pNetworkInterface):
	pNetworkInterface_(pNetworkInterface)
{
}

PacketReceiver::~PacketReceiver()
{
}

void PacketReceiver::process()
{
	FSocket *socket = pNetworkInterface_->socket();
	uint32 DataSize = 0;

	while (socket->HasPendingData(DataSize))
	{
		MemoryStream* s = new MemoryStream();
		s->resize(FMath::Min(DataSize, 65507u));

		int32 BytesRead = 0;
		if (socket->Recv(s->data(), s->size(), BytesRead))
		{
		}
	}
}