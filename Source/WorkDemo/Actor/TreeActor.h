// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "TreeActor.generated.h"

/**
 * 
 */
UCLASS()
class WORKDEMO_API ATreeActor : public AActorBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Tree")
	TArray<TSubclassOf<USkeletalMeshComponent>> MeshComponent;
};
