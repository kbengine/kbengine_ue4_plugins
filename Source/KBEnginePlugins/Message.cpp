
#include "KBEnginePluginsPrivatePCH.h"
#include "Message.h"

Message::Message():
	id(0),
	name(""),
	msglen(-1),
	argsType(0)
{
}

Message::~Message()
{
}
