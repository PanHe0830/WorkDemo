// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "MonsterSpawnActor.generated.h"

/** 
	怪物生成点
**/

/**
 * 
 */
UCLASS()
class WORKDEMO_API AMonsterSpawnActor : public AActorBase
{
	GENERATED_BODY()
public:
	AMonsterSpawnActor();

	virtual void BeginPlay() override;

private:
	void SpawnNpcCharacter();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ANpcCharacterBase> NpcCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	FTimerHandle NpcTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnRate = 5.0f;
};
