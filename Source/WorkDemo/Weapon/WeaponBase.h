// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/** 
	ÎäÆ÷Àà
**/

class USphereComponent;
class UWidgetComponent;

UCLASS()
class WORKDEMO_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire(FVector HitTarget);

private:
	UFUNCTION()
	void BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USphereComponent* ShpereComponent;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UWidgetComponent* PickUpWidget;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UAnimationAsset* WeaponFireAnimation; // ÎäÆ÷¿ª»ð¶¯»­

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ACasingBase> CasingClass; // µ¯¿Ç

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AProjectileBase> ProjectileClass; // ×Óµ¯

public:
	void SetHideWidgetComponent();
};
