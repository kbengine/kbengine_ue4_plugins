// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KBECommon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogKBEngine, Log, All);

#define KBE_ASSERT check

typedef uint16 MessageID;
typedef uint16 MessageLength;

/** 安全的释放一个指针内存 */
#define SAFE_RELEASE(i)										\
	if (i)													\
		{													\
			delete i;										\
			i = NULL;										\
		}

/** 安全的释放一个指针数组内存 */
#define SAFE_RELEASE_ARRAY(i)								\
	if (i)													\
		{													\
			delete[] i;										\
			i = NULL;										\
		}

USTRUCT(BlueprintType)
struct FKServerErr
{
	GENERATED_USTRUCT_BODY()

	FKServerErr()
	: name()
	, descr()
	, id(0)
	{
	}

	UPROPERTY(Category = ServerErr, EditAnywhere)
	FString name;

	UPROPERTY(Category = ServerErr, EditAnywhere)
	FString descr;

	UPROPERTY(Category = ServerErr, EditAnywhere)
	uint16 id;
};

// 客户端的类别
// http://www.kbengine.org/docs/programming/clientsdkprogramming.html
// http://www.kbengine.org/cn/docs/programming/clientsdkprogramming.html
UENUM(BlueprintType)
enum class EKCLIENT_TYPE : uint8
{
	CLIENT_TYPE_UNKNOWN		UMETA(DisplayName = "unknown"),
	CLIENT_TYPE_MOBILE		UMETA(DisplayName = "Mobile"),
	CLIENT_TYPE_WIN			UMETA(DisplayName = "Windows"),
	CLIENT_TYPE_LINUX		UMETA(DisplayName = "Linux"),
	CLIENT_TYPE_MAC			UMETA(DisplayName = "Mac"),
	CLIENT_TYPE_BROWSER		UMETA(DisplayName = "Browser"),
	CLIENT_TYPE_BOTS		UMETA(DisplayName = "Bots"),
	CLIENT_TYPE_MINI		UMETA(DisplayName = "Mini"),
};

UCLASS()
class KBENGINEPLUGINS_API AKBECommon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKBECommon();
	
};
