// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "AssertActor.h"
#include "WorkDemo/SubSystem/BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "WorkDemo/Actor/AssertActor.h"

ATreeActor::ATreeActor()
{
    
}

void ATreeActor::BeginPlay()
{
	Super::BeginPlay();

    if (StaticMeshs.Num() > 0 && ActorStaticMesh)
    {
        int32 Index = FMath::RandRange(0, StaticMeshs.Num() - 1);
        UStaticMesh* SelectedMesh = StaticMeshs[Index];

        if (SelectedMesh)
        {
            ActorStaticMesh->SetStaticMesh(SelectedMesh);
            SetMeshCollision();
        }
    }

    OnTakeAnyDamage.AddDynamic(this,&ATreeActor::RecvDamage);
}

void ATreeActor::Destroyed()
{
    Super::Destroyed();

}


void ATreeActor::RecvDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

    if (Health <= 0)
    {
        Destroy();

        FVector Location = GetActorLocation();
        FRotator Rotator = GetActorRotation();
        UBuildSubsystem* build = GetWorld()->GetGameInstance()->GetSubsystem<UBuildSubsystem>();
        if (build)
        {
            build->BuildSystemSpawnActor(AssertActor, Location, Rotator);
        }
    }
}

void ATreeActor::SetMeshCollision()
{
    ActorStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    ActorStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}
