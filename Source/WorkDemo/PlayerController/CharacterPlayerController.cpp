// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "WorkDemo/HUD/MainWidget.h"

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
}

void ACharacterPlayerController::SetBagVisibility()
{
    if(bFlag)
    {
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Hidden);
        UE_LOG(LogTemp, Warning, TEXT("visible"));
    }
    else
    {
        MainWidgetInstance->SetBagUiVisibility(ESlateVisibility::Visible);
        UE_LOG(LogTemp, Warning, TEXT("hidder"));
    }
    bFlag = !bFlag;
}
