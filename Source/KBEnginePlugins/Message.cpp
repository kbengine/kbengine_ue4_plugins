
#include "KBEnginePluginsPrivatePCH.h"
#include "Message.h"

TMap<MessageID, Message*> Message::loginappMessages;
TMap<MessageID, Message*> Message::baseappMessages;
TMap<MessageID, Message*> Message::clientMessages;

TMap<FString, Message*> Message::messages;

Message::Message(MessageID mid, const FString& mname, int16 mmsglen, uint8 margsType):
	id(mid),
	name(mname),
	msglen(mmsglen),
	argsType(margsType)
{
}

Message::~Message()
{
}

void Message::clear()
{
	for (auto& Elem : Message::messages)
		delete Elem.Value;

	Message::messages.Empty();

	bindFixedMessage();
}

void Message::bindFixedMessage()
{
	// 引擎协议说明参见: http://www.kbengine.org/cn/docs/programming/clientsdkprogramming.html
	Message::setMessage(TEXT("Loginapp_importClientMessages"), new Message(5, TEXT("importClientMessages"), 0, 0 /*, new List<Byte>(), null*/));
	Message::setMessage(TEXT("Loginapp_hello"), new Message(4, TEXT("hello"), -1, 0 /*, new List<Byte>(), null*/));
}

Message* Message::getMessage(const FString& messageName)
{
	return NULL;
}

void Message::setMessage(const FString& messageName, Message* pMessage)
{

}