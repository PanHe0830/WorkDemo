// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuildSubsystem.generated.h"

class UAssertResourceManager;
class UTestObject;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UBuildSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:
	UAssertResourceManager* ResourceManager;
};
