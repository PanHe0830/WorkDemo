// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertActor.h"
#include "Components/WidgetComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "LandscapeProxy.h"
#include "WorkDemo/WorkDemoCharacter.h"

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
    }
    else
    {
        Destroy();
    }
    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAssertActor::SphereComponentBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this,&AAssertActor::SphereComponentEndOverlag);
}

bool AAssertActor::CheckAssertPosition()
{
    UWorld* World = GetWorld();
    if (World)
    {
        FHitResult HitResult;
        // ������ײ��ѯ����
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this); // ���Ը��ӵ���Actor
        //CollisionParams.AddIgnoredComponent(SphereComponent); // ����������ײ��
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

        if (HitResult.GetActor() && !HitResult.GetActor()->IsA<ALandscapeProxy>())
        {
            //UE_LOG(LogTemp, Warning, TEXT("%s  hitname = %s"), *HitResult.BoneName.ToString(), *HitResult.GetActor()->GetName());
            return false;
        }
        return true;
    }
    return false;
}

void AAssertActor::SetCurrentAssert()
{
    AssertAndAssertNum.Empty();
    for (int i = 0; i < MaxAssert; i++)
    {
        int RandNum = FMath::RandRange(0, AssertType.Num() - 1);
        EAssertType Type = AssertType[RandNum]; // �����Դ������
        float OneDecimalValue = FMath::RoundToFloat(FMath::FRandRange(0.0f, 10.0f) * 10.0f) / 10.0f; // �����Դ������
        if (AssertAndAssertNum.Find(Type))
        {
            AssertAndAssertNum[Type] += OneDecimalValue;
        }
        else
        {
            AssertAndAssertNum.Add(Type, OneDecimalValue);
        }
    }

    // չʾ��Դ Mesh
    int VisualIndex = 0;
    for (auto& Elem : AssertAndAssertNum)
    {
        EAssertType Type = Elem.Key;
        float Amount = Elem.Value;

        if (!ResourceMeshMap.Contains(Type)) continue;

        int Count = FMath::CeilToInt(Amount); // ÿ����Դ���ɼ��� Mesh��1����λ��һ�� Mesh
        for (int i = 0; i < Count; i++)
        {
            FString CompName = FString::Printf(TEXT("Mesh_%d_%d"), (int32)Type, i);
            UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, *CompName);
            MeshComp->RegisterComponent();
            MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            MeshComp->SetStaticMesh(ResourceMeshMap[Type]);

            // ��Ȼ�ڷţ���΢���һ��
            FVector RandomOffset(
                FMath::FRandRange(-50.f, 50.f),
                FMath::FRandRange(-50.f, 50.f),
                FMath::FRandRange(0.f, 30.f)
            );
            FRotator RandomRotation(0.f, FMath::FRandRange(0.0f, 360.0f), 0.f);

            MeshComp->SetRelativeLocation(RandomOffset);
            MeshComp->SetRelativeRotation(RandomRotation);

            // ��ѡ����
            //float Scale = FMath::FRandRange(0.8f, 1.2f);
            //MeshComp->SetRelativeScale3D(FVector(Scale));
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

void AAssertActor::SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    SetWidgetVisibility(true);
}

void AAssertActor::SphereComponentEndOverlag(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    SetWidgetVisibility(false);
}
