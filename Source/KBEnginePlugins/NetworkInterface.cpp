
#include "KBEnginePluginsPrivatePCH.h"
#include "NetworkInterface.h"
#include "PacketReceiver.h"
#include "PacketSender.h"

NetworkInterface::NetworkInterface():
	socket_(NULL),
	pPacketSender_(NULL),
	pPacketReceiver_(NULL)
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
	reset();

	FIPv4Address ip1;
	FIPv4Address::Parse(ip, ip1);


	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip1.Value);
	addr->SetPort(port);

	socket_ = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	return valid() && socket_->Connect(*addr);;
}

bool NetworkInterface::send(FString datas)
{
	if (!valid())
	{
		return false;
	}

	if (!pPacketSender_)
		pPacketSender_ = new PacketSender(this);

	return pPacketSender_->send(datas);
}

void NetworkInterface::process()
{
	if (!valid())
		return;

	if (!pPacketReceiver_)
		pPacketReceiver_ = new PacketReceiver(this);

	pPacketReceiver_->process();
}