// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "WorkDemo/WorkDemoCharacter.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
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
	if(PickUpWidget)
	{
		PickUpWidget->SetVisibility(false);
	}
}

