// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "WorkDemo/HUD/MainWidget.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "GameFramework/Actor.h"
#include "WorkDemo/HUD/InventoryWidget.h"
#include "WorkDemo/Component/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorkDemo/Actor/TreeActor.h"
#include "WorkDemo/SubSystem/BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "WorkDemo/Component/CombatComponent.h"

ACharacterPlayerController::ACharacterPlayerController()
{
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
    bShowMouseCursor = false;
    bEnableMouseOverEvents = true;
    bEnableTouchOverEvents = true;
}

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
        //FInputModeGameAndUI mode;
        //SetInputMode(mode);
        SetShowMouseCursor(false);
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Visible);
        RefreshUi();

        //FInputModeGameAndUI mode;
        //SetInputMode(mode);
        SetShowMouseCursor(true);
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
            RefreshUi();
            return;
        }

        UCombatComponent* Combat = character->GetCombatComponent();
        if (Combat)
        {
            Combat->EquipWeapon(character->FirstWeapon);
            character->SetStartingAimRotation();
            return;
        }
    }

    //if (bFlag)
    //{
    //    RefreshUi();
    //}
}

void ACharacterPlayerController::DamageTree()
{
    //UE_LOG(LogTemp, Warning, TEXT("DamageTree"));
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
            }
        }

        character->FireButtonPress();
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

bool ACharacterPlayerController::CheckAssertDown()
{


    return false;
}

void ACharacterPlayerController::BeginBuild(int32 TypeId)
{
    InputComponent->BindAxis("BuildBuild", this, &ACharacterPlayerController::ChangeActorLocation);
    InputComponent->BindAction("BuildMouseClicked", IE_Pressed, this , &ACharacterPlayerController::MouseLeftClicked);
    
    bBuildFlag = true;
    int ScreenX;
    int ScreenY;
    GetViewportSize(ScreenX, ScreenY);
    FVector2D ScreenCenter(ScreenX / 2.f, ScreenY / 2.f);

    FVector WorldLocation3D;
    FVector WorldDirection3D;
    if (DeprojectScreenPositionToWorld(ScreenX / 2.f, ScreenY / 2.f, WorldLocation3D, WorldDirection3D))
    {
        UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
        if (Build)
        {
            TArray<AActor*> IgnoreArry;
            IgnoreArry.Add(GetCharacter());
            auto BiuldTmap = Build->ResourceManager->BuildTypeAndNeed;
            Build->BuildSystemFirstViewCheck(BiuldTmap[static_cast<EBuildType>(TypeId)].BuildBluePrint, WorldLocation3D, WorldDirection3D, IgnoreArry);
        }
    }
}

void ACharacterPlayerController::ChangeActorLocation(float XY)
{
    if (!bBuildFlag) return;

    int ScreenX;
    int ScreenY;
    GetViewportSize(ScreenX, ScreenY);
    FVector2D ScreenCenter(ScreenX / 2.f, ScreenY / 2.f);
    FVector WorldLocation3D;
    FVector WorldDirection3D;
    if (DeprojectScreenPositionToWorld(ScreenX / 2.f, ScreenY / 2.f, WorldLocation3D, WorldDirection3D))
    {
        FVector TraceStart = WorldLocation3D;
        FVector TraceEnd = TraceStart + (WorldDirection3D * 3000.f); // 3米范围

        FHitResult Hit;
        FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(ViewportTrace), true);
        TraceParams.AddIgnoredActor(GetCharacter());

        // 执行射线检测
        bool bHit = GetWorld()->LineTraceSingleByChannel(
            Hit,
            TraceStart,
            TraceEnd,   
            ECC_Visibility,
            TraceParams
        );

        if (bHit)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.Location.ToString());
            UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
            if (Build)
            {
                Build->ChangePreviewActorPosition(Hit.Location);
            }
        }
    }
}

void ACharacterPlayerController::MouseLeftClicked()
{
    UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
    if (Build->DoBoxCheck())
    {
        Build->SetActorColliksion();
    
        InputComponent->RemoveActionBinding("BuildMouseClicked", IE_Pressed);
        InputComponent->RemoveAxisBinding("BuildBuild");
        bBuildFlag = false;
    }

}
