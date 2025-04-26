// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

void UBuildSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    SpawnLocation = FVector::ZeroVector;

	FString BlueprintPath = TEXT("/Game/BluePrint/ResourceManager/BP_AssertResourceManager.BP_AssertResourceManager_C");
	UClass* BlueprintClass = StaticLoadClass(
		UAssertResourceManager::StaticClass(),
		nullptr,
		*BlueprintPath
	);
	
	if (BlueprintClass)
	{
		ResourceManager = NewObject<UAssertResourceManager>(GetTransientPackage(), BlueprintClass);
	}
}

void UBuildSubsystem::BuildSystemSpawnActor(TSubclassOf<AActor> Actor, FVector Location, FRotator Rotator)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* actor = World->SpawnActor<AActor>(
			Actor,
			Location,
			Rotator,
			param
		);
		if (!actor)
		{
			UE_LOG(LogTemp , Warning , TEXT("spawn failed"));
		}
	}
}

bool UBuildSubsystem::CheckBuildLocation(const FVector& Location, const FRotator& Rotation, const FVector& Extents) const
{
    UWorld* World = GetWorld();
    if (!World) return false;

    //UE_LOG(LogTemp, Warning, TEXT("Location is : %s  --  Extents is : %s"), *Location.ToString() , *Extents.ToString());

    // ������ײ��ѯ����
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(PreviewBuilding); // ���Ը��ӵ���Actor

    // ִ�к���׷�ټ��
    FHitResult HitResult;
    bool bHit = World->SweepSingleByChannel(
        HitResult,
        Location,
        Location,
        Rotation.Quaternion(),
        ECC_WorldDynamic, // ʹ���ʺ�����Ŀ����ײͨ��
        FCollisionShape::MakeBox(Extents),
        CollisionParams
    );

    return bHit;
}

bool UBuildSubsystem::BuildSystemSpawnActor(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters SpawnParams)
{
    UWorld* World = GetWorld();
    if (!World) return false;

    PreviewBuilding = World->SpawnActor<AActor>(
        BuildingTemplate,
        Location,
        Rotation,
        SpawnParams
    );

    if (PreviewBuilding)
    {
        TArray<UBoxComponent*> BoxComponents;
        PreviewBuilding->GetComponents<UBoxComponent>(BoxComponents);

        for (auto ite : BoxComponents)
        {
            ite->SetHiddenInGame(false);  // �ؼ�������Ϸ����ʾ
            ite->SetVisibility(true, true);
            ite->SetLineThickness(2.0f);  // �����߿��ϸ
        }

        return true;
    }
    return false;
}

void UBuildSubsystem::SetCollisionBoxColor()
{
    TArray<UBoxComponent*> BoxComponents;
    PreviewBuilding->GetComponents<UBoxComponent>(BoxComponents);

    for (int i = 0; i < BoxComponents.Num(); i++)
    {
        FVector BoxExtents = BoxComponents[i]->GetScaledBoxExtent();
        FVector BoxLocation = BoxComponents[i]->GetComponentLocation();
        FRotator BoxRotation = BoxComponents[i]->GetComponentRotation();

        bool bFlag = CheckBuildLocation(BoxLocation, BoxRotation, BoxExtents);
        // ���λ���Ƿ����
        if (bFlag)
        {
            // ����ײ ��ɫ
            BoxComponents[i]->ShapeColor = FColor::Red;
            //UE_LOG(LogTemp, Warning, TEXT("����ײ"));
        }
        else
        {
            // ����ײ ��ɫ
            BoxComponents[i]->ShapeColor = FColor::Green;
        }
    }
}

bool UBuildSubsystem::ShowPreview(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation)
{
    if (!BuildingTemplate) return false; //if (PreviewBuilding) PreviewBuilding->Destroy();

    // ����Ԥ������
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (BuildSystemSpawnActor(BuildingTemplate, Location, Rotation, SpawnParams))
    {
        SpawnLocation = Location;
    }
    else
    {
        SpawnLocation = FVector::ZeroVector;
        return false;
    }

    SetCollisionBoxColor();

    return true;
}

void UBuildSubsystem::DestoryCurrentActor()
{
    if (PreviewBuilding)
    {
        PreviewBuilding->Destroy();
        PreviewBuilding = nullptr;
    }
}

void UBuildSubsystem::ChangePreviewActorPosition(FVector position)
{
    if (PreviewBuilding == nullptr) return;
    PreviewBuilding->SetActorLocation(position);

    SpawnLocation = position;

    SetCollisionBoxColor();
}

void UBuildSubsystem::SetCollisionBoxVisibilityHide()
{
    TArray<UBoxComponent*> BoxComponents;
    PreviewBuilding->GetComponents<UBoxComponent>(BoxComponents);

    for (int i = 0; i < BoxComponents.Num(); i++)
    {
        BoxComponents[i]->SetHiddenInGame(true);
        BoxComponents[i]->SetVisibility(false, true);
        BoxComponents[i]->SetLineThickness(0.0f);  // �����߿��ϸ

        BoxComponents[i]->SetComponentTickEnabled(false);

        UE_LOG(LogTemp, Warning, TEXT("Component Valid: %d"), IsValid(BoxComponents[i]));
        UE_LOG(LogTemp, Warning, TEXT("HiddenInGame: %d"), BoxComponents[i]->bHiddenInGame);
    }

    PreviewBuilding->SetActorLocation(SpawnLocation);
}

bool UBuildSubsystem::GetCurrentIsRight()
{
    TArray<UBoxComponent*> BoxComponents;
    PreviewBuilding->GetComponents<UBoxComponent>(BoxComponents);

    for (int i = 0; i < BoxComponents.Num(); i++)
    {
        if (BoxComponents[i]->ShapeColor == FColor::Red)
        {
            return false;
        }
    }

    return true;
}
