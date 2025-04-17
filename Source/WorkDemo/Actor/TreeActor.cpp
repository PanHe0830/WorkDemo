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
        }
        //UE_LOG(LogTemp , Warning , TEXT("spawn tree"));
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
    }
}
