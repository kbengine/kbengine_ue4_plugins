// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(KBEngine, Log, All);

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
	: (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
	: (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
	: (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
	: TEXT("[Standalone] "))

#define FUNC_NAME TEXT(__func__)

#if PLATFORM_WINDOWS
#define FUNC_NAME TEXT(__FUNCTION__)
#endif

#if PLATFORM_ANDROID
#define  FUNC_NAME __func__
#endif

#define TRACE(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (Msg == "") \
	{ \
		UE_LOG(KBEngine, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this)); \
	} \
		else \
	{ \
		UE_LOG(KBEngine, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	} \
	CLEAR_WARN_COLOR(); \
}

#define TRACESTATIC(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEngine, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg); \
	CLEAN_WARN_COLOR(); \
}

#define TRACEWARN(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_YELLOW); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEngine, Log, TEXT("**WARNING** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
}

#define TRACEERROR(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_RED); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(KBEngine, Log, TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg); \
	CLEAR_WARN_COLOR(); \
}


#define SCREENDEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (Msg == "") \
	{ \
		TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
		FCString::Sprintf(StdMsg, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this)); \
		GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, StdMsg); \
	} \
	else \
	{ \
		GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, Msg); \
	} \
}

class FKBEnginePluginsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

