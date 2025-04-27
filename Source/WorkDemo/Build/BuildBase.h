// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildBase.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;

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

private:
	UPROPERTY(EditAnywhere, Category = "Base")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Base")
	float Health = 100;

	/* ������ʾ������� */
	UPROPERTY(EditAnywhere, Category = "Base")
	UWidgetComponent* WidgetComponent;

	/* ��Ҫ�����ʱ�� */
	UPROPERTY(EditAnywhere, Category = "Base")
	float BuildTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Base")
	EBuildType BuildType;

public:
	FORCEINLINE float GetBuildTime() { return BuildTime; };

	FORCEINLINE EBuildType GetBuildType() { return BuildType; };
};
