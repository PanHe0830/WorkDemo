// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "WorkDemo/HUD/MainWidget.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "GameFramework/Actor.h"
#include "WorkDemo/HUD/InventoryWidget.h"
#include "WorkDemo/Component/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorkDemo/Actor/TreeActor.h"

void ACharacterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MainWidget)
    {
        MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidget);
        if (MainWidgetInstance)
        {
            MainWidgetInstance->AddToViewport();
        }
    }
}

void ACharacterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("OpenBag" , IE_Pressed , this , &ACharacterPlayerController::SetBagVisibility); // I
    InputComponent->BindAction("PickUpAssert", IE_Pressed, this, &ACharacterPlayerController::PickUpAssert); // E
    InputComponent->BindAction("TreeDamage", IE_Pressed, this, &ACharacterPlayerController::DamageTree); // mouse left
}

void ACharacterPlayerController::SetBagVisibility()
{
    if(bFlag)
    {
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Hidden);
        //UE_LOG(LogTemp, Warning, TEXT("visible"));
    }
    else
    {
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Visible);
        RefreshUi();
        //UE_LOG(LogTemp, Warning, TEXT("hidder"));
    }
    bFlag = !bFlag;

}

void ACharacterPlayerController::PickUpAssert()
{
    AWorkDemoCharacter* character = Cast<AWorkDemoCharacter>(GetCharacter());
    if (character)
    {
        AActor* actor = character->AssertActor;
        if (actor)
        {
            character->PickUpCurrentAssertInInventoryComponent();
            actor->Destroy();
        }
    }

    if (bFlag)
    {
        RefreshUi();
    }
}

void ACharacterPlayerController::DamageTree()
{
    AWorkDemoCharacter* character = Cast<AWorkDemoCharacter>(GetCharacter());
    FVector StartLocation;
    FVector EndLocation;
    if (character)
    {
        USkeletalMeshComponent* Mesh = character->GetMesh();
        if (Mesh)
        {
            StartLocation = Mesh->GetSocketLocation("LineTraceStart"); // LineTraceStart 是我在角色网格体上新添加的插槽，用于射线检测

            FVector ForwardVector; // 角色当前的方向
            ForwardVector = character->GetActorForwardVector();
            EndLocation = StartLocation + (ForwardVector * 100.f);

            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(character);  // 排除自己

            FHitResult HitResult;
            UWorld* World = GetWorld();
            if (World)
            {
                bool bflag = World->LineTraceSingleByChannel(
                    HitResult,
                    StartLocation,
                    EndLocation,
                    ECollisionChannel::ECC_WorldStatic,
                    CollisionParams
                );
            }

            AActor* HitActor = HitResult.GetActor();
            //ATreeActor* TreeActor = Cast<ATreeActor>(HitActor);
            if (HitActor)
            {
                UGameplayStatics::ApplyDamage(
                    HitActor,
                    CurrentDamage,
                    this,
                    character,
                    UDamageType::StaticClass()
                );

                character->PlayHitTreeMontage();
            }
        }
    }
}

void ACharacterPlayerController::RefreshUi()
{
    AWorkDemoCharacter* character = Cast<AWorkDemoCharacter>(GetCharacter());
    if (character)
    {
        UInventoryComponent* Inventory = character->GetInventoryComponent();
        if (Inventory && MainWidgetInstance)
        {
            //UE_LOG(LogTemp, Warning, TEXT("RefreshUi controller %d") , Inventory->GetItems().Num());
            //Inventory->PrintItemsTypeAndNum();
            MainWidgetInstance->RefreshBagUi(Inventory->GetItems());
        }
    }
}

void ACharacterPlayerController::CheckDistanceByViewChannel()
{

}
