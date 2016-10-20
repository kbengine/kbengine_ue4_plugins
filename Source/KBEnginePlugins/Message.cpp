
#include "KBEnginePluginsPrivatePCH.h"
#include "Message.h"

TMap<MessageID, Message*> Message::loginappMessages;
TMap<MessageID, Message*> Message::baseappMessages;
TMap<MessageID, Message*> Message::clientMessages;

TMap<FString, Message*> Message::messages;

Message::Message(MessageID mid, const FString& mname, int16 mmsglen, uint8 margsType, const TArray<uint8>& msgargtypes):
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

	Message::loginappMessages.Empty();
	Message::baseappMessages.Empty();
	Message::clientMessages.Empty();

	bindFixedMessage();
}

void Message::bindFixedMessage()
{
	if (Message::messages.Num() > 0)
		return;

	// 引擎协议说明参见: http://www.kbengine.org/cn/docs/programming/clientsdkprogramming.html
	Message::messages.Add(TEXT("Loginapp_importClientMessages"), new Message(5, TEXT("importClientMessages"), 0, 0, TArray<uint8>()));
	Message::messages.Add(TEXT("Loginapp_hello"), new Message(4, TEXT("hello"), -1, -1, TArray<uint8>()));

	Message::messages.Add(TEXT("Baseapp_importClientMessages"), new Message(207, TEXT("importClientMessages"), 0, 0, TArray<uint8>()));
	Message::messages.Add(TEXT("Baseapp_importClientEntityDef"), new Message(208, TEXT("importClientMessages"), 0, 0, TArray<uint8>()));
	Message::messages.Add(TEXT("Baseapp_hello"), new Message(200, TEXT("hello"), -1, -1, TArray<uint8>()));

	Message::messages.Add(TEXT("Client_onHelloCB"), new Message(521, TEXT("Client_onHelloCB"), -1, -1, TArray<uint8>()));

	Message::clientMessages.Add(Message::messages[TEXT("Client_onHelloCB")]->id, Message::messages[TEXT("Client_onHelloCB")]);

	Message::messages.Add(TEXT("Client_onScriptVersionNotMatch"), new Message(522, TEXT("Client_onScriptVersionNotMatch"), -1, -1, TArray<uint8>()));
	Message::clientMessages.Add(Message::messages[TEXT("Client_onScriptVersionNotMatch")]->id, Message::messages[TEXT("Client_onScriptVersionNotMatch")]);

	Message::messages.Add(TEXT("Client_onVersionNotMatch"), new Message(523, TEXT("Client_onVersionNotMatch"), -1, -1, TArray<uint8>()));
	Message::clientMessages.Add(Message::messages[TEXT("Client_onVersionNotMatch")]->id, Message::messages[TEXT("Client_onVersionNotMatch")]);

	Message::messages.Add(TEXT("Client_onImportClientMessages"), new Message(518, TEXT("Client_onImportClientMessages"), -1, -1, TArray<uint8>()));
	Message::clientMessages.Add(Message::messages[TEXT("Client_onImportClientMessages")]->id, Message::messages[TEXT("Client_onImportClientMessages")]);
}


