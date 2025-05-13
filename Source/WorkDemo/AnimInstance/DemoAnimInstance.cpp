// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoAnimInstance.h"
#include "WorkDemo/WorkDemoCharacter.h"

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

	IsEquip = DemoCharacter->GetIsEquipWeapon();
}
