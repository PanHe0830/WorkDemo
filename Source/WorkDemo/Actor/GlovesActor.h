// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "GlovesActor.generated.h"

/**
	这是一个手套的actor
*/

/**
 * 
 */
UCLASS()
class WORKDEMO_API AGlovesActor : public AActorBase
{
	GENERATED_BODY()
	
public:
	AGlovesActor();

	virtual void BeginPlay() override;
};
