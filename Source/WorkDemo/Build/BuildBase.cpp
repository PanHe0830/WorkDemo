// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

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
	//MeshComponent->SetGenerateOverlapEvents(true);  // 启用生成重叠事件

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	WidgetComponent->SetupAttachment(MeshComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(MeshComponent);

	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//CollisionBox->SetGenerateOverlapEvents(true);  // 启用生成重叠事件

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

