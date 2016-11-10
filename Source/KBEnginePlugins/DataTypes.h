// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KBECommon.h"

class MemoryStream;

/*
	entitydef所支持的基本数据类型
	改模块中的类抽象出了所有的支持类型并提供了这些类型的数据序列化成二进制数据与反序列化操作（主要用于网络通讯的打包与解包）
*/
class KBENGINEPLUGINS_API KBEDATATYPE_BASE
{
public:
		virtual void bind()
		{
		}

		/*
		static bool isNumeric(object v)
		{
		return v is sbyte || v is byte ||
		v is short || v is ushort ||
		v is int || v is uint ||
		v is long || v is ulong ||
		v is char || v is decimal || v is float ||
		v is double || v is Int16 || v is Int64 ||
		v is UInt16 || v is UInt64 ||
		v is Boolean || v is bool;
		}

		virtual object createFromStream(MemoryStream stream)
		{
			return null;
		}
		
		virtual void addToStream(Bundle stream, object v)
		{
		}
		
		virtual object parseDefaultValStr(string v)
		{
			return null;
		}
		
		virtual bool isSameType(object v)
		{
			return v == null;
		}
		*/
protected:

};
