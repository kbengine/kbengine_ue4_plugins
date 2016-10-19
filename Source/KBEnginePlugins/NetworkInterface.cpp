
#include "KBEnginePluginsPrivatePCH.h"
#include "NetworkInterface.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "MemoryStream.h"

NetworkInterface::NetworkInterface():
	socket_(NULL),
	pPacketSender_(NULL),
	pPacketReceiver_(NULL),
	TickConnectingDelegateHandle()
{
}

NetworkInterface::~NetworkInterface()
{
	close();
}

void NetworkInterface::reset()
{
	close();
}

void NetworkInterface::close()
{
	FTicker::GetCoreTicker().RemoveTicker(TickConnectingDelegateHandle);

	if (socket_)
	{
		socket_->Close();
		TRACE("network closed!");
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket_);
	}

	socket_ = NULL;

	SAFE_RELEASE(pPacketSender_);
	SAFE_RELEASE(pPacketReceiver_);
}

bool NetworkInterface::valid()
{
	return socket_ != NULL;
}

bool NetworkInterface::connectTo(FString ip, uint16 port)
{
	TRACE("will connect to %s:%d ...", *ip, port);

	reset();

	FIPv4Address ip1;
	FIPv4Address::Parse(ip, ip1);


	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip1.Value);
	addr->SetPort(port);

	socket_ = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	if (!valid())
	{
		TRACEERROR("socket could't be created!");
		return false;
	}
	
	if (!socket_->SetNonBlocking(true))
	{
		TRACEERROR("socket->SetNonBlocking error(%d)!", *ip, port,
			(int32)ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode());
	}

	bool didConnect = socket_->Connect(*addr);

	if (didConnect)
	{
		TickConnectingDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &NetworkInterface::TickConnecting), 0.1f);
	}
	else
	{
		TRACEERROR("connect %s:%d error(%d)!", *ip, port, 
			(int32)ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode());
	}

	return didConnect;
}

bool NetworkInterface::send(MemoryStream* pMemoryStream)
{
	if (!valid())
	{
		return false;
	}

	if (!pPacketSender_)
		pPacketSender_ = new PacketSender(this);

	return pPacketSender_->send(pMemoryStream);
}

void NetworkInterface::process()
{
	if (!valid())
		return;

	if (!pPacketReceiver_)
		pPacketReceiver_ = new PacketReceiver(this);

	pPacketReceiver_->process();
}

bool NetworkInterface::TickConnecting(float InDeltaTime)
{
	ESocketConnectionState state = socket_->GetConnectionState();
	if (state == SCS_Connected)
	{
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		socket_->GetPeerAddress(*addr);

		TRACE("connect to %s success!", *addr->ToString(true));
		FTicker::GetCoreTicker().RemoveTicker(TickConnectingDelegateHandle);
	}

	return true; // Tick again
}