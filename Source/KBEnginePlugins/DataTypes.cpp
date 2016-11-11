
#include "KBEnginePluginsPrivatePCH.h"
#include "DataTypes.h"
#include "MemoryStream.h"
#include "Runtime/Core/Public/Misc/Variant.h"

FVariant* KBEDATATYPE_INT8::createFromStream(MemoryStream& stream)
{
	int8 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_INT8::addToStream(Bundle& stream, FVariant& v)
{
	int8 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_INT8::parseDefaultValStr(FString& v)
{
	int8 val = (int8)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_INT8::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Int8;
}

FVariant* KBEDATATYPE_INT16::createFromStream(MemoryStream& stream)
{
	int16 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_INT16::addToStream(Bundle& stream, FVariant& v)
{
	int16 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_INT16::parseDefaultValStr(FString& v)
{
	int16 val = (int16)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_INT16::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Int16;
}

FVariant* KBEDATATYPE_INT32::createFromStream(MemoryStream& stream)
{
	int32 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_INT32::addToStream(Bundle& stream, FVariant& v)
{
	int32 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_INT32::parseDefaultValStr(FString& v)
{
	int32 val = (int32)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_INT32::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Int32;
}

FVariant* KBEDATATYPE_INT64::createFromStream(MemoryStream& stream)
{
	int64 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_INT64::addToStream(Bundle& stream, FVariant& v)
{
	int64 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_INT64::parseDefaultValStr(FString& v)
{
	int64 val = (int64)FCString::Atoi64(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_INT64::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Int64;
}

FVariant* KBEDATATYPE_UINT8::createFromStream(MemoryStream& stream)
{
	uint8 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_UINT8::addToStream(Bundle& stream, FVariant& v)
{
	uint8 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_UINT8::parseDefaultValStr(FString& v)
{
	uint8 val = (uint8)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_UINT8::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::UInt8;
}

FVariant* KBEDATATYPE_UINT16::createFromStream(MemoryStream& stream)
{
	uint16 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_UINT16::addToStream(Bundle& stream, FVariant& v)
{
	uint16 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_UINT16::parseDefaultValStr(FString& v)
{
	uint16 val = (uint16)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_UINT16::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::UInt16;
}

FVariant* KBEDATATYPE_UINT32::createFromStream(MemoryStream& stream)
{
	uint32 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_UINT32::addToStream(Bundle& stream, FVariant& v)
{
	uint32 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_UINT32::parseDefaultValStr(FString& v)
{
	uint32 val = (uint32)FCString::Atoi(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_UINT32::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::UInt32;
}

FVariant* KBEDATATYPE_UINT64::createFromStream(MemoryStream& stream)
{
	uint64 val = 0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_UINT64::addToStream(Bundle& stream, FVariant& v)
{
	uint64 val = v;
	stream << val;
}

FVariant* KBEDATATYPE_UINT64::parseDefaultValStr(FString& v)
{
	uint64 val = (uint64)FCString::Atoi64(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_UINT64::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::UInt64;
}

FVariant* KBEDATATYPE_FLOAT::createFromStream(MemoryStream& stream)
{
	float val = 0.f;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_FLOAT::addToStream(Bundle& stream, FVariant& v)
{
	float val = v;
	stream << val;
}

FVariant* KBEDATATYPE_FLOAT::parseDefaultValStr(FString& v)
{
	float val = (float)FCString::Atof(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_FLOAT::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Float;
}

FVariant* KBEDATATYPE_DOUBLE::createFromStream(MemoryStream& stream)
{
	double val = 0.0;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_DOUBLE::addToStream(Bundle& stream, FVariant& v)
{
	double val = v;
	stream << val;
}

FVariant* KBEDATATYPE_DOUBLE::parseDefaultValStr(FString& v)
{
	double val = (double)FCString::Atof(*v);
	return new FVariant(val);
}

bool KBEDATATYPE_DOUBLE::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Double;
}

FVariant* KBEDATATYPE_STRING::createFromStream(MemoryStream& stream)
{
	FString val;
	stream >> val;
	return new FVariant(val);
}

void KBEDATATYPE_STRING::addToStream(Bundle& stream, FVariant& v)
{
	FString val = v;
	stream << val;
}

FVariant* KBEDATATYPE_STRING::parseDefaultValStr(FString& v)
{
	return new FVariant(v);
}

bool KBEDATATYPE_STRING::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::String || v.GetType() == EVariantTypes::Ansichar;
}

FVariant* KBEDATATYPE_VECTOR2::createFromStream(MemoryStream& stream)
{
	uint32 size = 0;
	stream >> size;
	if (2 != size)
	{
		ERROR_MSG("KBEDATATYPE_VECTOR2::createFromStream: size(%d) is error!", size);
	}

	FVector2D val;
	stream >> val.X >> val.Y;
	return new FVariant(val);
}

void KBEDATATYPE_VECTOR2::addToStream(Bundle& stream, FVariant& v)
{
	FVector2D val = v;
	stream << val.X << val.Y;
}

FVariant* KBEDATATYPE_VECTOR2::parseDefaultValStr(FString& v)
{
	return new FVariant(FVector2D());
}

bool KBEDATATYPE_VECTOR2::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Vector2d;
}

FVariant* KBEDATATYPE_VECTOR3::createFromStream(MemoryStream& stream)
{
	uint32 size = 0;
	stream >> size;
	if (3 != size)
	{
		ERROR_MSG("KBEDATATYPE_VECTOR3::createFromStream: size(%d) is error!", size);
	}

	FVector val;
	stream >> val.X >> val.Y >> val.Z;
	return new FVariant(val);
}

void KBEDATATYPE_VECTOR3::addToStream(Bundle& stream, FVariant& v)
{
	FVector val = v;
	stream << val.X << val.Y << val.Z;
}

FVariant* KBEDATATYPE_VECTOR3::parseDefaultValStr(FString& v)
{
	return new FVariant(FVector());
}

bool KBEDATATYPE_VECTOR3::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Vector;
}

FVariant* KBEDATATYPE_VECTOR4::createFromStream(MemoryStream& stream)
{
	uint32 size = 0;
	stream >> size;
	if (4 != size)
	{
		ERROR_MSG("KBEDATATYPE_VECTOR4::createFromStream: size(%d) is error!", size);
	}

	FVector4 val;
	stream >> val.X >> val.Y >> val.Z >> val.W;
	return new FVariant(val);
}

void KBEDATATYPE_VECTOR4::addToStream(Bundle& stream, FVariant& v)
{
	FVector4 val = v;
	stream << val.X << val.Y << val.Z << val.W;
}

FVariant* KBEDATATYPE_VECTOR4::parseDefaultValStr(FString& v)
{
	return new FVariant(FVector4());
}

bool KBEDATATYPE_VECTOR4::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::Vector4;
}

FVariant* KBEDATATYPE_PYTHON::createFromStream(MemoryStream& stream)
{
	TArray<uint8> val;
	stream.readBlob(val);
	return new FVariant(val);
}

void KBEDATATYPE_PYTHON::addToStream(Bundle& stream, FVariant& v)
{
	TArray<uint8> val = v;
	stream.appendBlob(val);
}

FVariant* KBEDATATYPE_PYTHON::parseDefaultValStr(FString& v)
{
	return new FVariant(TArray<uint8>());
}

bool KBEDATATYPE_PYTHON::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::ByteArray;
}

FVariant* KBEDATATYPE_UNICODE::createFromStream(MemoryStream& stream)
{
	FString val;
	stream.readUTF8String(val);
	return new FVariant(val);
}

void KBEDATATYPE_UNICODE::addToStream(Bundle& stream, FVariant& v)
{
	FString val = v;
	stream.appendUTF8String(val);
}

FVariant* KBEDATATYPE_UNICODE::parseDefaultValStr(FString& v)
{
	return new FVariant(v);
}

bool KBEDATATYPE_UNICODE::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::String || v.GetType() == EVariantTypes::Widechar
		|| v.GetType() == EVariantTypes::Ansichar;
}

FVariant* KBEDATATYPE_MAILBOX::createFromStream(MemoryStream& stream)
{
	TArray<uint8> val;
	stream.readBlob(val);
	return new FVariant(val);
}

void KBEDATATYPE_MAILBOX::addToStream(Bundle& stream, FVariant& v)
{
	TArray<uint8> val = v;
	stream.appendBlob(val);
}

FVariant* KBEDATATYPE_MAILBOX::parseDefaultValStr(FString& v)
{
	return new FVariant(TArray<uint8>());
}

bool KBEDATATYPE_MAILBOX::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::ByteArray;
}

FVariant* KBEDATATYPE_BLOB::createFromStream(MemoryStream& stream)
{
	TArray<uint8> val;
	stream.readBlob(val);
	return new FVariant(val);
}

void KBEDATATYPE_BLOB::addToStream(Bundle& stream, FVariant& v)
{
	TArray<uint8> val = v;
	stream.appendBlob(val);
}

FVariant* KBEDATATYPE_BLOB::parseDefaultValStr(FString& v)
{
	return new FVariant(TArray<uint8>());
}

bool KBEDATATYPE_BLOB::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::ByteArray;
}

void KBEDATATYPE_ARRAY::bind()
{
}

FVariant* KBEDATATYPE_ARRAY::createFromStream(MemoryStream& stream)
{
	TArray<uint8> val;
	stream.readBlob(val);
	return new FVariant(val);
}

void KBEDATATYPE_ARRAY::addToStream(Bundle& stream, FVariant& v)
{
	TArray<uint8> val = v;
	stream.appendBlob(val);
}

FVariant* KBEDATATYPE_ARRAY::parseDefaultValStr(FString& v)
{
	return new FVariant(TArray<uint8>());
}

bool KBEDATATYPE_ARRAY::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::ByteArray;
}

void KBEDATATYPE_FIXED_DICT::bind()
{
}

FVariant* KBEDATATYPE_FIXED_DICT::createFromStream(MemoryStream& stream)
{
	TArray<uint8> val;
	stream.readBlob(val);
	return new FVariant(val);
}

void KBEDATATYPE_FIXED_DICT::addToStream(Bundle& stream, FVariant& v)
{
	TArray<uint8> val = v;
	stream.appendBlob(val);
}

FVariant* KBEDATATYPE_FIXED_DICT::parseDefaultValStr(FString& v)
{
	return new FVariant(TArray<uint8>());
}

bool KBEDATATYPE_FIXED_DICT::isSameType(FVariant& v)
{
	return v.GetType() == EVariantTypes::ByteArray;
}
