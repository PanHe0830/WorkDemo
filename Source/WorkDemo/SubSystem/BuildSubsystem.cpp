// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LandscapeProxy.h"

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

    // 设置碰撞查询参数
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(PreviewBuilding); // 忽略附加到的Actor

    // 执行盒体追踪检测
    FHitResult HitResult;
    bool bHit = World->SweepSingleByChannel(
        HitResult,
        Location,
        Location,
        Rotation.Quaternion(),
        ECC_WorldDynamic, // 使用适合你项目的碰撞通道
        FCollisionShape::MakeBox(Extents),
        CollisionParams
    );

    
    if (HitResult.GetActor())
    {
        if (HitResult.GetActor()->IsA<ALandscapeProxy>())
        {
            return false;
        }
        UE_LOG(LogTemp , Warning , TEXT("%s"), *HitResult.GetActor()->GetName());
    }

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
            ite->SetHiddenInGame(false);  // 关键：在游戏中显示
            ite->SetVisibility(true, true);
            ite->SetLineThickness(2.0f);  // 设置线框粗细
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
        // 检查位置是否可用
        if (bFlag)
        {
            // 有碰撞 红色
            BoxComponents[i]->ShapeColor = FColor::Red;
            //UE_LOG(LogTemp, Warning, TEXT("有碰撞"));
        }
        else
        {
            // 无碰撞 绿色
            BoxComponents[i]->ShapeColor = FColor::Green;
        }
    }
}

void UBuildSubsystem::BuildSystemFirstViewCheck(TSubclassOf<AActor> BuildingTemplate, FVector WorldLocation, FVector Direction,TArray<AActor*> IgnoreActors)
{
    //FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(ViewportTrace), true);
    //TraceParams.AddIgnoredActor(this); // 忽略自身

    UWorld* World = GetWorld();
    if (World)
    {
        // 射线参数
        FVector TraceStart = WorldLocation;
        FVector TraceEnd = TraceStart + (Direction * 3000.f); // 3米范围

        FHitResult Hit;
        FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(ViewportTrace), true);
        TraceParams.AddIgnoredActors(IgnoreActors);

        // 执行射线检测
        bool bHit = GetWorld()->LineTraceSingleByChannel(
            Hit, 
            TraceStart, 
            TraceEnd, 
            ECC_Visibility, 
            TraceParams
        );

        // 可视化调试射线
        //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        if (bHit)
        {
            // 输出命中对象
            PreviewBuilding = World->SpawnActor<AActor>(
                BuildingTemplate,
                Hit.Location,
                FRotator(0,0,0),
                SpawnParams
            );
        }
        else
        {
            // 没命中
            PreviewBuilding = World->SpawnActor<AActor>(
                BuildingTemplate,
                TraceEnd,
                FRotator(0, 0, 0),
                SpawnParams
            );
        }
        
        if (PreviewBuilding)
        {
            UStaticMeshComponent* tempmesh = PreviewBuilding->FindComponentByClass<UStaticMeshComponent>();
            if (tempmesh)
            {
                tempmesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
                //tempmesh->SetCollisionResponseToChannel();
            }
            UBoxComponent* Box = PreviewBuilding->FindComponentByClass<UBoxComponent>();
            if (Box)
            {
                Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
            }
        }
    }
}

bool UBuildSubsystem::ShowPreview(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation)
{
    if (!BuildingTemplate) return false; //if (PreviewBuilding) PreviewBuilding->Destroy();

    // 创建预览建筑
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

    //SetCollisionBoxColor();
}

void UBuildSubsystem::SetCollisionBoxVisibilityHide()
{
    TArray<UBoxComponent*> BoxComponents;
    PreviewBuilding->GetComponents<UBoxComponent>(BoxComponents);

    for (int i = 0; i < BoxComponents.Num(); i++)
    {
        BoxComponents[i]->SetHiddenInGame(true);
        BoxComponents[i]->SetVisibility(false, true);
        BoxComponents[i]->SetLineThickness(0.0f);  // 设置线框粗细

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

bool UBuildSubsystem::DoBoxCheck()
{
    //FVector BoxCenter = PreviewBuilding->GetActorLocation();
    //FVector BoxHalfExtent = FVector(200.f, 200.f, 200.f); // 你房子的碰撞范围（可改为实际值）
    //TArray<AActor*> IgnoreActors;
    //TArray<AActor*> OutActors;
    //
    //// 过滤类型：WorldStatic（建筑、地面等）
    //TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ////ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
    ////ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
    //
    //bool bBlocked = UKismetSystemLibrary::BoxOverlapActors(
    //    GetWorld(),
    //    BoxCenter,
    //    BoxHalfExtent,
    //    //ObjectTypes,
    //    //nullptr,          // 任何Actor类型都检测
    //    //IgnoreActors,
    //    //OutActors
    //);

    FVector Location = PreviewBuilding->GetActorLocation();
    UBoxComponent* BoxComponent = PreviewBuilding->FindComponentByClass<UBoxComponent>();
    FVector Extents = BoxComponent->GetScaledBoxExtent();
    FRotator Rotation(0, 0, 0);

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(PreviewBuilding); // 忽略附加到的Actor

    // 执行盒体追踪检测
    FHitResult HitResult;
    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Location,
        Location,
        Rotation.Quaternion(),
        ECC_Visibility, // 使用适合你项目的碰撞通道
        FCollisionShape::MakeBox(Extents),
        CollisionParams
    );

    DrawDebugBox(GetWorld(), Location, Extents, FColor::Red, false, 1.f, 0, 1.0f);

    if (HitResult.GetActor())
    {
        if (HitResult.GetActor()->IsA<ALandscapeProxy>())
        {
            return true;
        }
        UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
    }
    // true 有碰撞 false，无碰撞
    return !bHit;
}

void UBuildSubsystem::SetActorColliksion()
{
    if (PreviewBuilding)
    {
        UStaticMeshComponent* tempmesh = PreviewBuilding->FindComponentByClass<UStaticMeshComponent>();
        if (tempmesh)
        {
            //tempmesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
            tempmesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,ECollisionResponse::ECR_Block);
            tempmesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
            tempmesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
            tempmesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);
            tempmesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
            UE_LOG(LogTemp , Warning , TEXT("==============================="));
        }
        UBoxComponent* Box = PreviewBuilding->FindComponentByClass<UBoxComponent>();
        if (Box)
        {
            Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
        }
    }
}
