// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSubsystem.h"
#include "Engine/World.h"

void UTimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("DayNightSubsystem Initialized"));
}

void UTimeSubsystem::Deinitialize()
{
    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("DayNightSubsystem Deinitialized"));
}

void UTimeSubsystem::Tick(float DeltaTime)
{
    if (!GWorld || GWorld->IsPaused())
        return;

    // �ƽ�ʱ�䣨����ÿ֡�ƽ� 0.04 Сʱ��
    TimeAccumulator += DeltaTime;
    float TimeStep = DeltaTime * TimeScale;
    TimeOfDay += TimeStep;

    if (TimeOfDay >= 24.0f)
        TimeOfDay -= 24.0f;

    OnTimeChanged.Broadcast(TimeOfDay);
}