// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABuildBase::ABuildBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,ECollisionResponse::ECR_Ignore);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	WidgetComponent->SetupAttachment(MeshComponent);

	//MeshComponent->SetCollisionEnabled(ECollisionEnabled::);
}

// Called when the game starts or when spawned
void ABuildBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

