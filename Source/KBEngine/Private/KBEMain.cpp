// Fill out your copyright notice in the Description page of Project Settings.

#include "KBEnginePrivatePCH.h"
#include "KBEMain.h"


// Sets default values for this component's properties
UKBEMain::UKBEMain()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	ip = "127.0.0.1";
	port = 20013;
	syncPlayer = true;
	useAliasEntityID = true;
	isOnInitCallPropertysSetMethods = true;
}


// Called when the game starts
void UKBEMain::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKBEMain::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

