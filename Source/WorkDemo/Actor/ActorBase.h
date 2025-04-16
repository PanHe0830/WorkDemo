// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class WORKDEMO_API AActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, Category = "Actor")
	//USkeletalMeshComponent* ActorSketalMesh;

	UPROPERTY(EditAnywhere, Category = "Actor")
	UBoxComponent* BoxCollicion;

	UPROPERTY(EditAnywhere, Category = "Actor")
	UStaticMeshComponent* ActorStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Actor")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Actor")
	float Health = 100.f;
};
