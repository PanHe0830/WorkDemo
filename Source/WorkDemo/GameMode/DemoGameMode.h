// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DemoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WORKDEMO_API ADemoGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;
};
