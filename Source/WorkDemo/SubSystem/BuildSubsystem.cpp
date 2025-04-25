// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"

void UBuildSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FString BlueprintPath = TEXT("/Game/BluePrint/ResourceManager/BP_AssertResourceManager.BP_AssertResourceManager_C");
	UClass* BlueprintClass = StaticLoadClass(
		UAssertResourceManager::StaticClass(),
		nullptr,
		*BlueprintPath
	);
	
	if (BlueprintClass)
	{
		ResourceManager = NewObject<UAssertResourceManager>(GetTransientPackage(), BlueprintClass);
	}
}

void UBuildSubsystem::BuildSystemSpawnActor(TSubclassOf<AActor> Actor, FVector Location, FRotator Rotator)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* actor = World->SpawnActor<AActor>(
			Actor,
			Location,
			Rotator,
			param
		);
		if (!actor)
		{
			UE_LOG(LogTemp , Warning , TEXT("spawn failed"));
		}
	}
}
