// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "WorkDemo/Weapon/WeaponBase.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::EquipWeapon(AWeaponBase* Weapon)
{
	if (DemoCharacter == nullptr || Weapon == nullptr) return;

	FirstWeapon = Weapon;
	AttachWeaponToLeftHand(Weapon);
	Weapon->SetOwner(DemoCharacter);
}

void UCombatComponent::AttachWeaponToLeftHand(AWeaponBase* Weapon)
{
	if (DemoCharacter == nullptr || DemoCharacter->GetMesh() == nullptr || Weapon == nullptr) return;
	const USkeletalMeshSocket* HandSocket = DemoCharacter->GetMesh()->GetSocketByName(FName("WeaponSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(Weapon, DemoCharacter->GetMesh());
	}
}

