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
	ATreeActor();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UFUNCTION()
	void RecvDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//UPROPERTY(EditAnywhere, Category = "Tree")
	//TArray<USkeletalMesh*> MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Tree")
	TArray<UStaticMesh*> StaticMeshs;
};
