// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeActor.h"
#include "Components/SkeletalMeshComponent.h"

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

    UE_LOG(LogTemp, Warning, TEXT("Tree Actor recv damage"));

    if (Health <= 0)
    {
        Destroy();
    }
}

void ATreeActor::SetMeshCollision()
{
    ActorStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    ActorStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //ActorStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
    ActorStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}
