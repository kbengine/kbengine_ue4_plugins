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
	const static size_t DEFAULT_SIZE = 0;

	MemoryStream() :
		rpos_(0), 
		wpos_(0),
		data_()
	{
		data_resize(DEFAULT_SIZE);
	}

	~MemoryStream()
	{
		clear(false);
	}

public:
	uint8* data() {
		return data_.GetData();
	}

	void clear(bool clearData)
	{
		if (clearData)
			data_.Empty();

		rpos_ = wpos_ = 0;
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
	void done() { read_skip(length()); }

	void data_resize(size_t newsize)
	{
		KBE_ASSERT(newsize <= 1310700);
		data_.SetNumUninitialized(newsize);
	}

	void resize(size_t newsize)
	{
		KBE_ASSERT(newsize <= 1310700);
		data_.SetNumUninitialized(newsize);
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

	uint8 operator[](uint32 pos)
	{
		return read<uint8>(pos);
	}

	MemoryStream &operator<<(uint8 value)
	{
		append<uint8>(value);
		return *this;
	}

	MemoryStream &operator<<(uint16 value)
	{
		append<uint16>(value);
		return *this;
	}

	MemoryStream &operator<<(uint32 value)
	{
		append<uint32>(value);
		return *this;
	}

	MemoryStream &operator<<(uint64 value)
	{
		append<uint64>(value);
		return *this;
	}

	MemoryStream &operator<<(int8 value)
	{
		append<int8>(value);
		return *this;
	}

	MemoryStream &operator<<(int16 value)
	{
		append<int16>(value);
		return *this;
	}

	MemoryStream &operator<<(int32 value)
	{
		append<int32>(value);
		return *this;
	}

	MemoryStream &operator<<(int64 value)
	{
		append<int64>(value);
		return *this;
	}

	MemoryStream &operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	MemoryStream &operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	/*
	MemoryStream &operator<<(const std::string &value)
	{
		append((uint8 const *)value.c_str(), value.length());
		append((uint8)0);
		return *this;
	}
	*/

	MemoryStream &operator<<(const char *str)
	{
		append((uint8 const *)str, str ? strlen(str) : 0);
		append((uint8)0);
		return *this;
	}

	MemoryStream &operator<<(bool value)
	{
		append<int8>(value);
		return *this;
	}

	MemoryStream &operator>>(bool &value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	MemoryStream &operator>>(uint8 &value)
	{
		value = read<uint8>();
		return *this;
	}

	MemoryStream &operator>>(uint16 &value)
	{
		value = read<uint16>();
		return *this;
	}

	MemoryStream &operator>>(uint32 &value)
	{
		value = read<uint32>();
		return *this;
	}

	MemoryStream &operator>>(uint64 &value)
	{
		value = read<uint64>();
		return *this;
	}

	MemoryStream &operator>>(int8 &value)
	{
		value = read<int8>();
		return *this;
	}

	MemoryStream &operator>>(int16 &value)
	{
		value = read<int16>();
		return *this;
	}

	MemoryStream &operator>>(int32 &value)
	{
		value = read<int32>();
		return *this;
	}

	MemoryStream &operator>>(int64 &value)
	{
		value = read<int64>();
		return *this;
	}

	MemoryStream &operator>>(float &value)
	{
		value = read<float>();
		return *this;
	}

	MemoryStream &operator>>(double &value)
	{
		value = read<double>();
		return *this;
	}

	/*
	MemoryStream &operator>>(std::string& value)
	{
		value.clear();
		while (length() > 0)
		{
			char c = read<char>();
			if (c == 0 || !isascii(c))
				break;

			value += c;
		}

		return *this;
	}
	*/

	MemoryStream &operator>>(char *value)
	{
		while (length() > 0)
		{
			char c = read<char>();
			if (c == 0 || !isascii(c))
				break;

			*(value++) = c;
		}

		*value = '\0';
		return *this;
	}

	template<typename T>
	void read_skip() { read_skip(sizeof(T)); }

	void read_skip(uint32 skip)
	{
		check(skip <= length());
		rpos_ += skip;
	}

	template <typename T> T read()
	{
		T r = read<T>(rpos_);
		rpos_ += sizeof(T);
		return r;
	}

	template <typename T> T read(uint32 pos) 
	{
		check(sizeof(T) <= length());

		T val = *((T *)(data() + pos));
		EndianConvert(val);
		return val;
	}

	void read(uint8 *dest, uint32 len)
	{
		check(len <= length());

		memcpy(dest, data() + rpos_, len);
		rpos_ += len;
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
			data_resize(wpos_ + cnt);

		memcpy((void*)&data()[wpos_], src, cnt);
		wpos_ += cnt;
	}

protected:
	uint32 rpos_;
	uint32 wpos_;
	TArray<uint8> data_;
};

template<>
inline void MemoryStream::read_skip<char*>()
{
	uint8 temp = 1;
	while (temp != 0)
		temp = read<uint8>();
}

template<>
inline void MemoryStream::read_skip<char const*>()
{
	read_skip<char*>();
}

/*
template<>
inline void MemoryStream::read_skip<std::string>()
{
	read_skip<char*>();
}
*/