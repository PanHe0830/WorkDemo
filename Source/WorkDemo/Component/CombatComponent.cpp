// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "WorkDemo/Weapon/WeaponBase.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

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

	if (DemoCharacter)
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult);
		HitTarget = HitResult.ImpactPoint;

		//DrawDebugSphere(GetWorld(), HitResult.Location, 30.f, 12, FColor::Red, true, 5.f);
	}
}

void UCombatComponent::EquipWeapon(AWeaponBase* Weapon)
{
	if (DemoCharacter == nullptr || Weapon == nullptr) return;

	FirstWeapon = Weapon;
	AttachWeaponToLeftHand(Weapon);
	Weapon->SetOwner(DemoCharacter);
	Weapon->SetHideWidgetComponent();
}

void UCombatComponent::FireButtonPress(bool bPressed)
{
	bFlag = bPressed;
	if (DemoCharacter && bFlag)
	{
		DemoCharacter->PlayFireMontage();
		FirstWeapon->Fire(HitTarget);

		DrawDebugSphere(GetWorld(), HitTarget, 30.f, 12, FColor::Black, true, 5.f);
	}
}

void UCombatComponent::AttachWeaponToLeftHand(AWeaponBase* Weapon)
{
	if (DemoCharacter == nullptr || DemoCharacter->GetMesh() == nullptr || Weapon == nullptr) return;
	//const USkeletalMeshSocket* HandSocket = DemoCharacter->GetMesh()->GetSocketByName(FName("WeaponSocket"));
	//if (HandSocket)
	//{
	//	HandSocket->AttachActor(Weapon, DemoCharacter->GetMesh());
	//}

	const USkeletalMeshSocket* HandSocket = DemoCharacter->GetMesh()->GetSocketByName(FName("WeaponSocket"));
	if (HandSocket && Weapon)
	{
		FTransform SocketTransform = HandSocket->GetSocketTransform(DemoCharacter->GetMesh());

		// 先将武器移动到 Socket 位置（可选）
		Weapon->SetActorTransform(SocketTransform);

		// 附加武器到 Mesh 的 Socket 上，使用 SnapToTarget 保证跟随旋转
		Weapon->AttachToComponent(DemoCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
	}
}

void UCombatComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		if (DemoCharacter)
		{
			float DistanceToCharacter = (DemoCharacter->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100.f);
		}

		FVector End = Start + CrosshairWorldDirection * 8000;

		GetWorld()->LineTraceSingleByChannel(
			TraceHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);
		//if (TraceHitResult.GetActor() && TraceHitResult.GetActor()->Implements<UInteractWithCrosshairsInterface>())
		//{
		//	HUDPackage.CrosshairsColor = FLinearColor::Red;
		//}
		//else
		//{
		//	HUDPackage.CrosshairsColor = FLinearColor::White;
		//}
	}
}