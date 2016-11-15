// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Math/RandomStream.h"
#include "Misc/NetworkGuid.h"
#include "KBECommon.h"

namespace EKBVarTypes
{
	const int32 Empty = 0;
	const int32 Ansichar = 1;
	const int32 Bool = 2;
	const int32 Box = 3;
	const int32 BoxSphereBounds = 4;
	const int32 ByteArray = 5;
	const int32 Color = 6;
	const int32 DateTime = 7;
	const int32 Double = 8;
	const int32 Enum = 9;
	const int32 Float = 10;
	const int32 Guid = 11;
	const int32 Int8 = 12;
	const int32 Int16 = 13;
	const int32 Int32 = 14;
	const int32 Int64 = 15;
	const int32 IntRect = 16;
	const int32 LinearColor = 17;
	const int32 Matrix = 18;
	const int32 Name = 19;
	const int32 Plane = 20;
	const int32 Quat = 21;
	const int32 RandomStream = 22;
	const int32 Rotator = 23;
	const int32 String = 24;
	const int32 Widechar = 25;
	const int32 Timespan = 26;
	const int32 Transform = 27;
	const int32 TwoVectors = 28;
	const int32 UInt8 = 29;
	const int32 UInt16 = 30;
	const int32 UInt32 = 31;
	const int32 UInt64 = 32;
	const int32 Vector = 33;
	const int32 Vector2d = 34;
	const int32 Vector4 = 35;
	const int32 IntPoint = 36;
	const int32 IntVector = 37;
	const int32 NetworkGUID = 38;
	const int32 KBVarArray = 39;
	const int32 KBVarMap = 40; /*TMap<FString, KBVar>*/
	const int32 Custom = 0x40;
};

/**
* Stub for variant type traits.
*
* Actual type traits need to be declared through template specialization for custom
* data types that are to be used in KBVar. Traits for the most commonly used built-in
* types are declared below.
*
* Complex types, such as structures and classes can be serialized into a byte array
* and then assigned to a variant. Note that you will be responsible for ensuring
* correct byte ordering when serializing those types.
*
* @param T The type to be used in KBVar.
*/
template<typename T> struct TKBVariantTraits
{
	static int32 GetType()
	{
		static_assert(!sizeof(T), "KBVar trait must be specialized for this type.");
		return EVariantTypes::Empty;
	}
};


/**
* Implements an extensible union of multiple types.
*
* Variant types can be used to store a range of different built-in types, as well as user
* defined types. The values are internally serialized into a byte array, which means that
* only FArchive serializable types are supported at this time.
*/
class KBVar
{
public:
	typedef TMap<FString, KBVar> KBVarMap;
	typedef TArray<KBVar> KBVarArray;

	/** Default constructor. */
	KBVar()
		: Type(EKBVarTypes::Empty)
	{ }

	/** Copy constructor. */
	KBVar(const KBVar& Other)
		: Type(Other.Type)
		, Value(Other.Value)
	{ }

	/**
	* Creates and initializes a new instance with the specified value.
	*
	* @param InValue The initial value.
	*/
	template<typename T>
	KBVar(T InValue)
	{
		FMemoryWriter writer(Value, true);
		writer << InValue;

		Type = TKBVariantTraits<T>::GetType();
	}

	/**
	* Creates and initializes a new instance from a byte array.
	*
	* Array values are passed straight through as an optimization. Please note that, if you
	* serialize any complex types into arrays and then store them in KBVar, you will be
	* responsible for ensuring byte ordering if the KBVar gets sent over the network.
	*
	* @param InValue- The initial value.
	*/
	KBVar(const TArray<uint8>& InArray)
		: Type(EKBVarTypes::ByteArray)
		, Value(InArray)
	{ }

	KBVar(const TArray<KBVar>& InArray)
		: Type(EKBVarTypes::KBVarArray)
		, Value()
	{ }

	KBVar(const TMap<FString, KBVar>& InMap)
		: Type(EKBVarTypes::KBVarMap)
		, Value()
	{ }

	/**
	* Creates and initializes a new instance from a TCHAR string.
	*
	* @param InString The initial value.
	*/
	KBVar(const TCHAR* InString)
	{
		*this = FString(InString);
	}

public:

	/**
	* Copy assignment operator.
	*
	* @param Other The value to assign.
	* @return This instance.
	*/
	KBVar& operator=(const KBVar& Other)
	{
		if (&Other != this)
		{
			Value = Other.Value;
			Type = Other.Type;
		}

		return *this;
	}

	/**
	* Assignment operator.
	*
	* @param T The type of the value to assign.
	* @param InValue The value to assign.
	* @return This instance.
	*/
	template<typename T>
	KBVar& operator=(T InValue)
	{
		FMemoryWriter Writer(Value, true);
		Writer << InValue;

		Type = TKBVariantTraits<T>::GetType();

		return *this;
	}

	/**
	* Assignment operator for byte arrays.
	*
	* Array values are passed straight through as an optimization. Please note that, if you
	* serialize any complex types into arrays and then store them in KBVar, you will be
	* responsible for ensuring byte ordering if the KBVar gets sent over the network.
	*
	* @param InArray The byte array to assign.
	* @return This instance.
	*/
	KBVar& operator=(const TArray<uint8> InArray)
	{
		Type = EKBVarTypes::ByteArray;
		Value = MoveTemp(InArray);

		return *this;
	}

	/**
	* Assignment operator for TCHAR strings.
	*
	* @param InString The value to assign.
	* @return This instance.
	*/
	KBVar& operator=(const TCHAR* InString)
	{
		*this = FString(InString);

		return *this;
	}


	/**
	* Implicit conversion operator.
	*
	* @param T The type to convert the value to.
	* @return The value converted to the specified type.
	*/
	template<typename T>
	operator T() const
	{
		return GetValue<T>();
	}

public:

	/**
	* Comparison operator for equality.
	*
	* @param Other The variant to compare with.
	* @return true if the values are equal, false otherwise.
	*/
	bool operator==(const KBVar& Other) const
	{
		return ((Type == Other.Type) && (Value == Other.Value));
	}

	/**
	* Comparison operator for inequality.
	*
	* @param Other The variant to compare with.
	* @return true if the values are not equal, false otherwise.
	*/
	bool operator!=(const KBVar& Other) const
	{
		return ((Type != Other.Type) || (Value != Other.Value));
	}

public:

	/**
	* Empties the value.
	*
	* @see IsEmpty
	*/
	void Empty()
	{
		Type = EKBVarTypes::Empty;

		Value.Empty();
	}

	/**
	* Checks whether the value is empty.
	*
	* @return true if the value is empty, false otherwise.
	*
	* @see Empty
	*/
	bool IsEmpty() const
	{
		return (Type == EKBVarTypes::Empty);
	}

	/**
	* Gets the stored value as a byte array.
	*
	* This method returns the internal representation of any value as an
	* array of raw bytes. To retrieve values of type TArray<uint8> use
	* GetValue<TArray<uint8>>() instead.
	*
	* @return Byte array.
	* @see GetValue
	*/
	const TArray<uint8>& GetBytes() const
	{
		return Value;
	}

	/**
	* Gets the stored value's size (in bytes).
	*
	* @return Size of the value.
	* @see GetType, GetValue
	*/
	int32 GetSize() const
	{
		return Value.Num();
	}

	/**
	* Gets the stored value's type.
	*
	* @return Type of the value.
	* @see GetSize, GetValue
	*/
	int32 GetType() const
	{
		return Type;
	}

	/**
	* Gets the stored value.
	*
	* This template function does not provide any automatic conversion between
	* convertible types. The exact type of the value to be extracted must be known.
	*
	* @return The value.
	* @see GetSize, GetType
	*/
	template<typename T>
	T GetValue() const
	{
		check((Type == TKBVariantTraits<T>::GetType()) || ((TKBVariantTraits<T>::GetType() == EKBVarTypes::UInt8) && (Type == EKBVarTypes::Enum)));

		T Result;

		FMemoryReader Reader(Value, true);
		Reader << Result;

		return Result;
	}

public:

	/**
	* Serializes the given variant type from or into the specified archive.
	*
	* @param Ar The archive to serialize from or into.
	* @param Variant The value to serialize.
	* @return The archive.
	*/
	friend FArchive& operator<<(FArchive& Ar, KBVar& Variant)
	{
		return Ar << Variant.Type << Variant.Value;
	}

private:

	/** Holds the type of the variant. */
	int32 Type;

	/** Holds the serialized value. */
	TArray<uint8> Value;
};


/**
* Gets the stored value for byte arrays.
*
* Array values are passed straight through as an optimization. Please note that, if you serialize
* any complex types into arrays and then store them in KBVar, you will be responsible for
* ensuring byte ordering if the KBVar gets send over the network.
*
* To retrieve any value as an array of serialized bytes, use GetBytes() instead.
*
* @return The byte array.
* @see GetBytes
*/
template<>
FORCEINLINE TArray<uint8> KBVar::GetValue<TArray<uint8> >() const
{
	check(Type == EKBVarTypes::ByteArray);

	return Value;
}

template<>
FORCEINLINE TArray<KBVar> FVariant::GetValue<TArray<KBVar> >() const
{
	check(Type == EKBVarTypes::KBVarArray);

	return TArray<KBVar>();
}

template<>
FORCEINLINE TMap<FString, KBVar> FVariant::GetValue<TMap<FString, KBVar> >() const
{
	check(Type == EKBVarTypes::KBVarMap);

	return TMap<FString, KBVar>();
}


/* Default KBVar traits for built-in types
*****************************************************************************/

/** Implements variant type traits for the built-in ANSICHAR type. */
template<> struct TKBVariantTraits<ANSICHAR>
{
	static int32 GetType() { return EKBVarTypes::Ansichar; }
};


/** Implements variant type traits for the built-in bool type. */
template<> struct TKBVariantTraits<bool>
{
	static int32 GetType() { return EKBVarTypes::Bool; }
};


/** Implements variant type traits for the built-in FBox type. */
template<> struct TKBVariantTraits<FBox>
{
	static int32 GetType() { return EKBVarTypes::Box; }
};


/** Implements variant type traits for the built-in FBoxSphereBounds type. */
template<> struct TKBVariantTraits<FBoxSphereBounds>
{
	static int32 GetType() { return EKBVarTypes::BoxSphereBounds; }
};


/** Implements variant type traits for byte arrays. */
template<> struct TKBVariantTraits<TArray<uint8> >
{
	static int32 GetType() { return EKBVarTypes::ByteArray; }
};


/** Implements variant type traits for the built-in FColor type. */
template<> struct TKBVariantTraits<FColor>
{
	static int32 GetType() { return EKBVarTypes::Color; }
};


/** Implements variant type traits for the built-in FDateTime type. */
template<> struct TKBVariantTraits<FDateTime>
{
	static int32 GetType() { return EKBVarTypes::DateTime; }
};


/** Implements variant type traits for the built-in double type. */
template<> struct TKBVariantTraits<double>
{
	static int32 GetType() { return EKBVarTypes::Double; }
};


/** Implements variant type traits for enumeration types. */
template<typename EnumType> struct TKBVariantTraits<TEnumAsByte<EnumType> >
{
	static int32 GetType() { return EKBVarTypes::Enum; }
};


/** Implements variant type traits for the built-in float type. */
template<> struct TKBVariantTraits<float>
{
	static int32 GetType() { return EKBVarTypes::Float; }
};


/** Implements variant type traits for the built-in FGuid type. */
template<> struct TKBVariantTraits<FGuid>
{
	static int32 GetType() { return EKBVarTypes::Guid; }
};


/** Implements variant type traits for the built-in int8 type. */
template<> struct TKBVariantTraits<int8>
{
	static int32 GetType() { return EKBVarTypes::Int8; }
};


/** Implements variant type traits for the built-in int16 type. */
template<> struct TKBVariantTraits<int16>
{
	static int32 GetType() { return EKBVarTypes::Int16; }
};


/** Implements variant type traits for the built-in int32 type. */
template<> struct TKBVariantTraits<int32>
{
	static int32 GetType() { return EKBVarTypes::Int32; }
};


/** Implements variant type traits for the built-in int64 type. */
template<> struct TKBVariantTraits<int64>
{
	static int32 GetType() { return EKBVarTypes::Int64; }
};


/** Implements variant type traits for the built-in FIntPoint type. */
template<> struct TKBVariantTraits<FIntPoint>
{
	static int32 GetType() { return EKBVarTypes::IntPoint; }
};


/** Implements variant type traits for the built-in FIntVector type. */
template<> struct TKBVariantTraits<FIntVector>
{
	static int32 GetType() { return EKBVarTypes::IntVector; }
};


/** Implements variant type traits for the built-in FIntRect type. */
template<> struct TKBVariantTraits<FIntRect>
{
	static int32 GetType() { return EKBVarTypes::IntRect; }
};


/** Implements variant type traits for the built-in FLinearColor type. */
template<> struct TKBVariantTraits<FLinearColor>
{
	static int32 GetType() { return EKBVarTypes::LinearColor; }
};


/** Implements variant type traits for the built-in FMatrix type. */
template<> struct TKBVariantTraits<FMatrix>
{
	static int32 GetType() { return EKBVarTypes::Matrix; }
};


/** Implements variant type traits for the built-in FPlane type. */
template<> struct TKBVariantTraits<FPlane>
{
	static int32 GetType() { return EKBVarTypes::Plane; }
};


/** Implements variant type traits for the built-in FQuat type. */
template<> struct TKBVariantTraits<FQuat>
{
	static int32 GetType() { return EKBVarTypes::Quat; }
};


/** Implements variant type traits for the built-in FName type. */
template<> struct TKBVariantTraits<FName>
{
	static int32 GetType() { return EKBVarTypes::Name; }
};


/** Implements variant type traits for the built-in FRandomStream type. */
template<> struct TKBVariantTraits<FRandomStream>
{
	static int32 GetType() { return EKBVarTypes::RandomStream; }
};


/** Implements variant type traits for the built-in FRotator type. */
template<> struct TKBVariantTraits<FRotator>
{
	static int32 GetType() { return EKBVarTypes::Rotator; }
};


/** Implements variant type traits for the built-in FString type. */
template<> struct TKBVariantTraits<FString>
{
	static int32 GetType() { return EKBVarTypes::String; }
};


/** Implements variant type traits for the built-in WIDECHAR type. */
template<> struct TKBVariantTraits<WIDECHAR>
{
	static int32 GetType() { return EKBVarTypes::Widechar; }
};


/** Implements variant type traits for the built-in FTimespan type. */
template<> struct TKBVariantTraits<FTimespan>
{
	static int32 GetType() { return EKBVarTypes::Timespan; }
};


/** Implements variant type traits for the built-in FTransform type. */
template<> struct TKBVariantTraits<FTransform>
{
	static int32 GetType() { return EKBVarTypes::Transform; }
};


/** Implements variant type traits for the built-in FTwoVectors type. */
template<> struct TKBVariantTraits<FTwoVectors>
{
	static int32 GetType() { return EKBVarTypes::TwoVectors; }
};


/** Implements variant type traits for the built-in uint8 type. */
template<> struct TKBVariantTraits<uint8>
{
	static int32 GetType() { return EKBVarTypes::UInt8; }
};


/** Implements variant type traits for the built-in uint16 type. */
template<> struct TKBVariantTraits<uint16>
{
	static int32 GetType() { return EKBVarTypes::UInt16; }
};


/** Implements variant type traits for the built-in uint32 type. */
template<> struct TKBVariantTraits<uint32>
{
	static int32 GetType() { return EKBVarTypes::UInt32; }
};


/** Implements variant type traits for the built-in uint64 type. */
template<> struct TKBVariantTraits<uint64>
{
	static int32 GetType() { return EKBVarTypes::UInt64; }
};


/** Implements variant type traits for the built-in FVector type. */
template<> struct TKBVariantTraits<FVector>
{
	static int32 GetType() { return EKBVarTypes::Vector; }
};


/** Implements variant type traits for the built-in FVector2D type. */
template<> struct TKBVariantTraits<FVector2D>
{
	static int32 GetType() { return EKBVarTypes::Vector2d; }
};


/** Implements variant type traits for the built-in FVector4 type. */
template<> struct TKBVariantTraits<FVector4>
{
	static int32 GetType() { return EKBVarTypes::Vector4; }
};


/** Implements variant type traits for the built-in NetworkGUID type. */
template<> struct TKBVariantTraits<FNetworkGUID>
{
	static int32 GetType() { return EKBVarTypes::NetworkGUID; }
};

/** Implements variant type traits for KBVar arrays. */
template<> struct TKBVariantTraits<TArray<KBVar>>
{
	static int32 GetType() { return EKBVarTypes::KBVarArray; }
};

/** Implements variant type traits for KBVar maps. */
template<> struct TKBVariantTraits<TMap<FString, KBVar>>
{
	static int32 GetType() { return EKBVarTypes::KBVarMap; }
};

