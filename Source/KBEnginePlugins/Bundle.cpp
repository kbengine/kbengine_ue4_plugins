
#include "KBEnginePluginsPrivatePCH.h"
#include "Bundle.h"
#include "MemoryStream.h"
#include "Message.h"
#include "NetworkInterface.h"

Bundle::Bundle():
	pCurrStream_(NULL),
	streams_(),
	numMessage_(0),
	messageLength_(0),
	pMsgtype_(NULL),
	curMsgStreamIndex_(0)
{
	pCurrStream_ = MemoryStream::createObject();
}

Bundle::~Bundle()
{
	MemoryStream::reclaimObject(pCurrStream_);
	pCurrStream_ = NULL;
}

Bundle* Bundle::createObject()
{
	return new Bundle();
}

void Bundle::reclaimObject(Bundle* obj)
{
	delete obj;
}

void Bundle::newMessage(Message* pMsg)
{
	fini(false);

	pMsgtype_ = pMsg;
	numMessage_ += 1;

//	writeUint16(msgtype.id);

//	if (pMsgtype_->msglen == -1)
	{
//		writeUint16(0);
		messageLength_ = 0;
	}

	curMsgStreamIndex_ = 0;
}

void Bundle::fini(bool issend)
{
	if (numMessage_ > 0)
	{
		writeMsgLength();

		streams_.Add(pCurrStream_);
		pCurrStream_ = MemoryStream::createObject();
	}

	if (issend)
	{
		numMessage_ = 0;
		pMsgtype_ = NULL;
	}

	curMsgStreamIndex_ = 0;
}

void Bundle::writeMsgLength()
{
	//if (pMsgtype_->msglen != -1)
	//	return;

	if (curMsgStreamIndex_ > 0)
	{
		pCurrStream_ = streams_[streams_.Num() - curMsgStreamIndex_];
	}

	uint8* data = pCurrStream_->data();
	data[2] = (uint8)(messageLength_ & 0xff);
	data[3] = (uint8)(messageLength_ >> 8 & 0xff);
}

void Bundle::checkStream(uint32 v)
{
	if (v > pCurrStream_->space())
	{
		streams_.Add(pCurrStream_);
		pCurrStream_ = MemoryStream::createObject();
		++curMsgStreamIndex_;
	}

	messageLength_ += v;
}