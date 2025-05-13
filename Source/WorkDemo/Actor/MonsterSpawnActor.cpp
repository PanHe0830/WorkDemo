// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnActor.h"
#include "WorkDemo/NpcCharacter/NpcCharacterBase.h"

AMonsterSpawnActor::AMonsterSpawnActor()
{

}

void AMonsterSpawnActor::BeginPlay()
{
	GetWorldTimerManager().SetTimer(NpcTimerHandle, this, &AMonsterSpawnActor::SpawnNpcCharacter, SpawnRate);
}

void AMonsterSpawnActor::SpawnNpcCharacter()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters Parameter;
		Parameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor<ANpcCharacterBase>(
			NpcCharacter, 
			GetActorLocation(), 
			FRotator(0, 0, 0), 
			Parameter
		);
	}
}
