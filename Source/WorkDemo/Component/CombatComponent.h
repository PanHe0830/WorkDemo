// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORKDEMO_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	friend class AWorkDemoCharacter;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void EquipWeapon(AWeaponBase* Weapon);

private:
	void AttachWeaponToLeftHand(AWeaponBase* Weapon);

	UPROPERTY()
	class AWorkDemoCharacter* DemoCharacter;

	UPROPERTY()
	AWeaponBase* FirstWeapon;

public:
	FORCEINLINE bool GetIsEquipWeapon() { return FirstWeapon == nullptr; };
};
