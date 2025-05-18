// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAnimInstance.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDemoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	DemoCharacter = Cast<AWorkDemoCharacter>(TryGetPawnOwner());
}

void UDemoAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (!DemoCharacter)
	{
		DemoCharacter = Cast<AWorkDemoCharacter>(TryGetPawnOwner());
	}
	if (!DemoCharacter) return;

	FVector Velocity = DemoCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	IsEquip = DemoCharacter->GetIsEquipWeapon();
	Falling = DemoCharacter->GetCharacterMovement()->IsFalling();

	AO_Yaw = DemoCharacter->GetAO_Yaw();
	AO_Pitch = DemoCharacter->GetAO_Pitch();
}
