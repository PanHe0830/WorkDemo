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

ACharacterPlayerController::ACharacterPlayerController()
{
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
    bShowMouseCursor = true;
    bEnableMouseOverEvents = true;
    bEnableTouchOverEvents = true;
    EnableInput(this);

    //FInputModeGameAndUI mode;
    //SetInputMode(mode);
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

bool ACharacterPlayerController::CheckAssertDown()
{


    return false;
}

void ACharacterPlayerController::BeginBuild(int32 TypeId)
{
    InputComponent->BindAxis("BuildBuild", this, &ACharacterPlayerController::ChangeActorLocation);
    InputComponent->BindAction("BuildMouseClicked", IE_Pressed, this , &ACharacterPlayerController::MouseLeftClicked);
    
    // TODO 
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // ECC_Visibility 表示检测可见物体
    FRotator Ratotor(0, 0, 0);
    UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
    if (Build)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Build is success"));
        auto BiuldTmap = Build->ResourceManager->BuildTypeAndNeed;
        if (Build->ShowPreview(BiuldTmap[static_cast<EBuildType>(TypeId)].BuildBluePrint, HitResult.Location, Ratotor))
        {
            SpawnLocation = HitResult.Location;
        }
    }
    else
    {
        InputComponent->RemoveActionBinding("BuildMouseClicked", IE_Pressed);
        InputComponent->RemoveAxisBinding("BuildBuild");
    }
}

void ACharacterPlayerController::ChangeActorLocation(float XY)
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult); // ECC_Visibility 表示检测可见物体

    UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
    FRotator Ratotor(0, 0, 0);
    if (Build)
    {
        Build->ChangePreviewActorPosition(HitResult.Location);
    }
}

void ACharacterPlayerController::MouseLeftClicked()
{
    UBuildSubsystem* Build = GetGameInstance()->GetSubsystem<UBuildSubsystem>();
    if (Build->GetCurrentIsRight())
    {
        Build->SetCollisionBoxVisibilityHide();
    
        InputComponent->RemoveActionBinding("BuildMouseClicked", IE_Pressed);
        InputComponent->RemoveAxisBinding("BuildBuild");
    }
}
