// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "KBEMain.generated.h"

/*
可以理解为插件的入口模块
在这个入口中安装了需要监听的事件(installEvents)，同时初始化KBEngine(initKBEngine)
*/
class KBEngineApp;


UCLASS(ClassGroup = "KBEngine", blueprintable, editinlinenew, hidecategories = (Object, LOD, Lighting, TextureStreaming), meta = (DisplayName = "KBEngine Main", BlueprintSpawnableComponent))
class KBENGINEPLUGINS_API UKBEMain : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:	
	// Sets default values for this component's properties
	UKBEMain();
	
	/**
	* Initializes the component.  Occurs at level startup. This is before BeginPlay (Actor or Component).
	* All Components in the level will be Initialized on load before any Actor/Component gets BeginPlay
	* Requires component to be registered, and bWantsInitializeComponent to be true.
	*/
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	* Ends gameplay for this component.
	* Called from AActor::EndPlay only if bHasBegunPlay is true
	*/
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	* Handle this component being Uninitialized.
	* Called from AActor::EndPlay only if bHasBeenInitialized is true
	*/
	virtual void UninitializeComponent() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	bool destroyKBEngine();

	UPROPERTY(EditAnywhere, Category = KBEngine)
	FString ip;

	UPROPERTY(EditAnywhere, Category = KBEngine)
	int port;

	UPROPERTY(EditAnywhere, Category = KBEngine)
	EKCLIENT_TYPE clientType;

	UPROPERTY(EditAnywhere, Category = KBEngine)
	bool syncPlayer;

	UPROPERTY(EditAnywhere, Category = KBEngine)
	bool useAliasEntityID;

	UPROPERTY(EditAnywhere, Category = KBEngine)
	bool isOnInitCallPropertysSetMethods;

	static KBEngineApp* pApp;
};
