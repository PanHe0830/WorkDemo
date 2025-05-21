// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WorkDemo/Weapon/CasingBase.h"
#include "WorkDemo/Weapon/ProjectileBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	ShpereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ShpereComponent->SetupAttachment(WeaponMesh);
	ShpereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShpereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ShpereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	PickUpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	PickUpWidget->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	PickUpWidget->SetVisibility(false);
	
	if (ShpereComponent)
	{
		ShpereComponent->OnComponentBeginOverlap.AddDynamic(this,&AWeaponBase::BeginOverLap);
		ShpereComponent->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::EndOverLap);
	}
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire(FVector HitTarget)
{
	if (WeaponFireAnimation)
	{
		WeaponMesh->PlayAnimation(WeaponFireAnimation, true);
	}

	if (CasingClass)
	{
		const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);

			UWorld* World = GetWorld();
			if (World)
			{
				World->SpawnActor<ACasingBase>(
					CasingClass,
					SocketTransform.GetLocation(),
					SocketTransform.GetRotation().Rotator()
				);
			}
		}
	}

	if (ProjectileClass)
	{
		APawn* InstigatorPawn = Cast<APawn>(GetOwner());
		const USkeletalMeshSocket* MuzzleFlashSocket = WeaponMesh->GetSocketByName(FName("MuzzleFlash"));
		UWorld* World = GetWorld();
		if (MuzzleFlashSocket && World)
		{
			FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(WeaponMesh);
			// From muzzle flash socket to hit location from TraceUnderCrosshairs
			FVector ToTarget = HitTarget - SocketTransform.GetLocation();
			FRotator TargetRotation = ToTarget.Rotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = InstigatorPawn;

			AProjectileBase* SpawnedProjectile = nullptr;
			SpawnedProjectile = World->SpawnActor<AProjectileBase>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
			SpawnedProjectile->FireInDirection(ToTarget.GetSafeNormal());

			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitTarget.ToString());

			DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitTarget, FColor::Green, true, 10.f);
			//DrawDebugSphere(GetWorld(), HitTarget, 30.f, 12, FColor::Red, true, 5.f);
			//DrawDebugLine(World, SocketTransform.GetLocation(), ToTarget, FColor::Red, true, 3.0f);
			//SpawnedProjectile->TraceStart = SocketTransform.GetLocation();
			//SpawnedProjectile->InitialVelocity = SpawnedProjectile->GetActorForwardVector() * SpawnedProjectile->InitialSpeed;
		}

		//const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("MuzzleFlash"));
		//if (AmmoEjectSocket)
		//{
		//	FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
		//
		//	UWorld* World = GetWorld();
		//	if (World)
		//	{
		//		World->SpawnActor<AProjectileBase>(
		//			ProjectileClass,
		//			SocketTransform.GetLocation(),
		//			SocketTransform.GetRotation().Rotator()
		//		);
		//	}
		//}
	}

}

void AWeaponBase::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PickUpWidget)
	{
		PickUpWidget->SetVisibility(true);
	}
	AWorkDemoCharacter* DemoCharacter = Cast<AWorkDemoCharacter>(OtherActor);
	if (DemoCharacter)
	{
		DemoCharacter->SetCurrentWeapon(this);
	}
	
}

void AWeaponBase::EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PickUpWidget)
	{
		PickUpWidget->SetVisibility(false);
	}
	AWorkDemoCharacter* DemoCharacter = Cast<AWorkDemoCharacter>(OtherActor);
	if (DemoCharacter)
	{
		DemoCharacter->SetCurrentWeapon(nullptr);
	}
}

void AWeaponBase::SetHideWidgetComponent()
{
	ShpereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if(PickUpWidget)
	{
		PickUpWidget->SetVisibility(false);
	}
}

