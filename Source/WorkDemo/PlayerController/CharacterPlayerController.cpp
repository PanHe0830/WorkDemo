// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "WorkDemo/HUD/MainWidget.h"
#include "WorkDemo/WorkDemoCharacter.h"
#include "GameFramework/Actor.h"
#include "WorkDemo/HUD/InventoryWidget.h"

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

    InputComponent->BindAction("OpenBag" , IE_Pressed , this , &ACharacterPlayerController::SetBagVisibility);
    InputComponent->BindAction("PickUpAssert", IE_Pressed, this, &ACharacterPlayerController::PickUpAssert);
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
            // TODO -- 将面前的资源放到背包中
        }
    }
}
