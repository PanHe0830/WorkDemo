// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildBase.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class UBoxComponent;

enum class EBuildType : uint8;

UCLASS()
class WORKDEMO_API ABuildBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Base")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Base")
	float Health = 100;

	/* 用于显示建造进度 */
	UPROPERTY(EditAnywhere, Category = "Base")
	UWidgetComponent* WidgetComponent;

	/* 需要建造的时间 */
	UPROPERTY(EditAnywhere, Category = "Base")
	float BuildTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Base")
	EBuildType BuildType;

	UPROPERTY(EditAnywhere, Category = "Base")
	UBoxComponent* CollisionBox;

public:
	FORCEINLINE float GetBuildTime() { return BuildTime; };

	FORCEINLINE EBuildType GetBuildType() { return BuildType; };

	FORCEINLINE UStaticMeshComponent* GetStaticMesh() { return MeshComponent; };
};
