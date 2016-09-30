// Fill out your copyright notice in the Description page of Project Settings.

#include "KBEnginePluginsPrivatePCH.h"
#include "KBEMain.h"
#include "KBEngine.h"

KBEngineApp* UKBEMain::pApp = NULL;

// Sets default values for this component's properties
UKBEMain::UKBEMain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...

	ip = "127.0.0.1";
	port = 20013;
	syncPlayer = true;
	useAliasEntityID = true;
	isOnInitCallPropertysSetMethods = true;
	clientType = EKCLIENT_TYPE::CLIENT_TYPE_WIN;
}

void UKBEMain::InitializeComponent()
{
	Super::InitializeComponent();
}

void UKBEMain::UninitializeComponent()
{
	Super::UninitializeComponent();
}

// Called when the game starts
void UKBEMain::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (UKBEMain::pApp == NULL)
		UKBEMain::pApp = new KBEngineApp();
}

void UKBEMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UKBEMain::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UKBEMain::destroyKBEngine()
{
	if (!UKBEMain::pApp)
		return false;

	delete UKBEMain::pApp;
	UKBEMain::pApp = NULL;

	return true;
}


