
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
//	while (socket->HasPendingData(DataSize))
	{
		FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
		Datagram->SetNumUninitialized(FMath::Min(DataSize, 65507u));

		int32 BytesRead = 0;
		if (socket->Recv(Datagram->GetData(), Datagram->Num(), BytesRead))
		{
			//nLiveEditorListenServer::FNetworkMessage Message;
			//*Datagram << Message;

			//ReplicateChanges(Message);
			//TransactionHistory->AppendTransaction(Message.Payload.ClassName, Message.Payload.PropertyName, Message.Payload.PropertyValue);
		}
	}
}