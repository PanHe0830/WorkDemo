// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertActor.h"
#include "Components/WidgetComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "LandscapeProxy.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "WorkDemo/HUD/PickUpWidget.h"
#include "TreeActor.h"
#include "WorkDemo/SubSystem/BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "Kismet/GameplayStatics.h"

AAssertActor::AAssertActor()
{
    ShowWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ShowWidget"));
    ShowWidget->SetupAttachment(RootComponent);
      
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AAssertActor::BeginPlay()
{
    Super::BeginPlay();

    bool bFlag = CheckAssertPosition();

    if (bFlag)
    {
        SetCurrentAssert();

        SetWidgetVisibility(false);

        SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAssertActor::SphereComponentBeginOverlap);
        SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAssertActor::SphereComponentEndOverlag);

        SetWidgetContent();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AssertActor destory"));
        Destroy();
    }
}

void AAssertActor::Destroyed()
{
    Super::Destroyed();

    // TODO -- 播放声音，显示特效
}

bool AAssertActor::CheckAssertPosition()
{
    UWorld* World = GetWorld();
    if (World)
    {
        AWorkDemoCharacter* Character = Cast<AWorkDemoCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
        FHitResult HitResult;
        // 设置碰撞查询参数
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this); // 忽略附加到的Actor
        CollisionParams.AddIgnoredActor(Character);
        TArray<UActorComponent*> Components;
        GetComponents(Components);
        for (UActorComponent* Component : Components)
        {
            if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Component))
            {
                CollisionParams.AddIgnoredComponent(Prim);
            }
        }

        World->SweepSingleByChannel(
            HitResult,
            GetActorLocation(),
            GetActorLocation(),
            GetActorRotation().Quaternion(),
            ECC_Vehicle,
            FCollisionShape::MakeSphere(SphereComponent->GetScaledSphereRadius()),
            CollisionParams
        );

        //DrawDebugSphere(World, GetActorLocation(), SphereComponent->GetScaledSphereRadius(), 24, FColor::Red,true , 10.0f);

        if (HitResult.GetActor() && !HitResult.GetActor()->IsA<ALandscapeProxy>() && !HitResult.GetActor()->IsA<ATreeActor>())
        {
            //UE_LOG(LogTemp, Warning, TEXT("%s  hitname = %s"), *HitResult.BoneName.ToString(), *HitResult.GetActor()->GetName());
            return false;
        }
        return true;
    }
    //UE_LOG(LogTemp, Warning, TEXT("world is nullptr"));
    return false;
}

void AAssertActor::SetCurrentAssert()
{
    AssertAndAssertNum.Empty();
    for (int i = 0; i < MaxAssert; i++)
    {
        int RandNum = FMath::RandRange(0, AssertType.Num() - 1);
        EAssertType Type = AssertType[RandNum]; // 获得资源的类型
        float OneDecimalValue = FMath::RoundToFloat(FMath::FRandRange(1.0f, 5.0f) * 10.0f) / 10.0f; // 获得资源的数量
        if (AssertAndAssertNum.Find(Type))
        {
            AssertAndAssertNum[Type] += OneDecimalValue;
        }
        else
        {
            AssertAndAssertNum.Add(Type, OneDecimalValue);
        }
    }

    UWorld* World = GetWorld();
    
    if (!World) return;

    // 展示资源 Mesh
    int VisualIndex = 0;
    for (auto& Elem : AssertAndAssertNum)
    {
        EAssertType Type = Elem.Key;
        float Amount = Elem.Value;

        UBuildSubsystem* Build = World->GetGameInstance()->GetSubsystem<UBuildSubsystem>();
        if (Build && Build->ResourceManager)
        {
            if (!Build->ResourceManager->AssertIconMap.Contains(Type)) return;

            int Count = FMath::CeilToInt(Amount); // 每个资源生成几个 Mesh，1个单位就一个 Mesh
            for (int i = 0; i < Count; i++)
            {
                FString CompName = FString::Printf(TEXT("Mesh_%d_%d"), (int32)Type, i);
                UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, *CompName);
                MeshComp->RegisterComponent();
                MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                MeshComp->SetStaticMesh(Build->ResourceManager->GetMeshByType(Type));

                // 自然摆放：稍微随机一点
                FVector RandomOffset(
                    FMath::FRandRange(-50.f, 50.f),
                    FMath::FRandRange(-50.f, 50.f),
                    FMath::FRandRange(0.f, 30.f)
                );
                FRotator RandomRotation(0.f, FMath::FRandRange(0.0f, 360.0f), 0.f);

                MeshComp->SetRelativeLocation(RandomOffset);
                MeshComp->SetRelativeRotation(RandomRotation);
            }
        }
    }
}

void AAssertActor::SetWidgetVisibility(bool bFlag)
{
    if (ShowWidget)
    {
        ShowWidget->SetVisibility(bFlag);
    }
}

void AAssertActor::SetWidgetContent()
{
    if (UUserWidget* UserWidget = ShowWidget->GetUserWidgetObject())
    {
        UPickUpWidget* InfoWidget = Cast<UPickUpWidget>(UserWidget);
        if (InfoWidget)
        {
            InfoWidget->SetResourceData(AssertAndAssertNum);
        }
    }
}

void AAssertActor::SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    SetWidgetVisibility(true);
    AWorkDemoCharacter* WrokDemoCharacter = Cast<AWorkDemoCharacter>(OtherActor);
    if (WrokDemoCharacter)
    {
        //UE_LOG(LogTemp , Warning , TEXT("WrokDemoCharacter is exist"));
        WrokDemoCharacter->SetCurrentCanPickUpAssertTypeAndNum(AssertAndAssertNum , this);
    }
}

void AAssertActor::SphereComponentEndOverlag(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    SetWidgetVisibility(false);
    AWorkDemoCharacter* WrokDemoCharacter = Cast<AWorkDemoCharacter>(OtherActor);
    if (WrokDemoCharacter)
    {
        WrokDemoCharacter->ClearCurrentCanPickUpAssertTypeAndNum();
    }
}
