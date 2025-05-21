// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/BoxComponent.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "WorkDemo/PlayerController/CharacterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "WorkDemo/WorkDemo.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Block);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	//ProjectileMovementComponent->SetIsReplicated(true);
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = InitialSpeed;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // 不受重力影响
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	StartLocation = GetActorLocation();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::FireInDirection(const FVector& ShootDirection)
{
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity = ShootDirection * InitialSpeed;
	}
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AWorkDemoCharacter* OwnerCharacter = Cast<AWorkDemoCharacter>(GetOwner());
	if (OwnerCharacter)
	{
		ACharacterPlayerController* OwnerController = Cast<ACharacterPlayerController>(OwnerCharacter->Controller);
		if (OwnerController)
		{
			UGameplayStatics::ApplyDamage(
				OtherActor, 
				Damage, 
				OwnerController, 
				this, 
				UDamageType::StaticClass()
			);
		}
	}
	FString HitName = OtherActor->GetName();
	FString HitActorName = Hit.GetActor()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("HitName Actor: %s , HitName OtherActor: %s"), *HitActorName , *HitName);
	//DrawDebugLine(GetWorld(), StartLocation, OtherActor->GetActorLocation(),FColor::Green,true,10.f);
	

	//UE_LOG(LogTemp , Warning , TEXT("%s"), *OtherActor->GetName())
	//
	Destroy();
}
