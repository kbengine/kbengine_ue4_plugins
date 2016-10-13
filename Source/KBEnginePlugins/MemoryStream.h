// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProperties.h"

namespace MemoryStreamConverter
{
	template <class T> 
	void swap(T& a, T& b)
	{
		T c(a); a = b; b = c;
	}

	template<size_t T>
	inline void convert(char *val)
	{
		swap(*val, *(val + T - 1));
		convert<T - 2>(val + 1);
	}

	template<> inline void convert<0>(char *) {}
	template<> inline void convert<1>(char *) {}            // ignore central byte

	template<typename T> inline void apply(T *val)
	{
		convert<sizeof(T)>((char *)(val));
	}

	inline void convert(char *val, size_t size)
	{
		if (size < 2)
			return;

		swap(*val, *(val + size - 1));
		convert(val + 1, size - 2);
	}
}

template<typename T> inline void EndianConvert(T& val) 
{ 
	if(!FGenericPlatformProperties::IsLittleEndian())
		MemoryStreamConverter::apply<T>(&val); 
}

template<typename T> inline void EndianConvertReverse(T&) 
{
	if (FGenericPlatformProperties::IsLittleEndian())
		MemoryStreamConverter::apply<T>(&val);
}

template<typename T> void EndianConvert(T*);         // will generate link error
template<typename T> void EndianConvertReverse(T*);  // will generate link error

inline void EndianConvert(uint8&) { }
inline void EndianConvert(int8&) { }
inline void EndianConvertReverse(uint8&) { }
inline void EndianConvertReverse(int8&) { }

/*
	二进制数据流模块
	能够将一些基本类型序列化(writeXXX)成二进制流同时也提供了反序列化(readXXX)等操作
*/
class KBENGINEPLUGINS_API MemoryStream
{
public:
	const static size_t DEFAULT_SIZE = 0x100;

	MemoryStream() :
		rpos_(0), 
		wpos_(0),
		data_()
	{
		data_resize(DEFAULT_SIZE);
	}

	~MemoryStream()
	{

	}

public:
	const uint8* data() const {
		return data_.GetData();
	}

	MemoryStream &operator<<(uint8 value)
	{
		append<uint8>(value);
		return *this;
	}

	// array的大小
	virtual size_t size() const { return data_.Num(); }

	// array是否为空
	virtual bool empty() const { return data_.Num() == 0; }

	// 读索引到与写索引之间的长度
	virtual size_t length() const { return rpos() >= wpos() ? 0 : wpos() - rpos(); }

	// 剩余可填充的大小
	virtual size_t space() const { return wpos() >= size() ? 0 : size() - wpos(); }

	// 将读索引强制设置到写索引，表示操作结束
	//void done() { read_skip(length()); }

	void data_resize(size_t newsize)
	{
		KBE_ASSERT(newsize <= 1310700);
		data_.Reset(newsize);
	}

	void resize(size_t newsize)
	{
		KBE_ASSERT(newsize <= 1310700);
		data_.Reset(newsize);
		rpos_ = 0;
		wpos_ = size();
	}

	void reserve(size_t ressize)
	{
		KBE_ASSERT(ressize <= 1310700);

		if (ressize > size())
			data_.Reserve(ressize);
	}

	uint32 rpos() const { return rpos_; }

	uint32 rpos(int rpos)
	{
		if (rpos < 0)
			rpos = 0;

		rpos_ = rpos;
		return rpos_;
	}

	uint32 wpos() const { return wpos_; }

	uint32 wpos(int wpos)
	{
		if (wpos < 0)
			wpos = 0;

		wpos_ = wpos;
		return wpos_;
	}

	template <typename T> void append(T value)
	{
		EndianConvert(value);
		append((uint8 *)&value, sizeof(value));
	}

	template<class T> void append(const T *src, size_t cnt)
	{
		return append((const uint8 *)src, cnt * sizeof(T));
	}

	void append(const uint8 *src, size_t cnt)
	{
		if (!cnt)
			return;

		KBE_ASSERT(size() < 10000000);

		if (size() < wpos_ + cnt)
			data_.Reset(wpos_ + cnt);

		memcpy((void*)&data()[wpos_], src, cnt);
		wpos_ += cnt;
	}

protected:
	uint32 rpos_;
	uint32 wpos_;
	TArray<uint8> data_;
};
