// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameMode.h"
#include "WorkDemo/SubSystem/TimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ADemoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	
}

void ADemoGameMode::BeginPlay()
{
	Super::BeginPlay();

    TArray<AActor*> OutActor;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(),FName("Tag"),);

    if (GetGameInstance())
    {
        UTimeSubsystem* TimeSystem = GetGameInstance()->GetSubsystem<UTimeSubsystem>();
        if (TimeSystem)
        {
            //TimeSystem->StartDayNightCycle();
            UE_LOG(LogTemp, Warning, TEXT("Game Mode Begin Play"));
        }
    }
}
