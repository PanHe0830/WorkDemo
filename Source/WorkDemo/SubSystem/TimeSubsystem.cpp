// Fill out your copyright notice in the Description page of Project                                                               Settings.


#include "TimeSubsystem.h"
#include "Engine/World.h"
#include "Curves/CurveFloat.h"
#include "WorkDemo/SubSystem/WeatherActor.h"

void UTimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UTimeSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UTimeSubsystem::SetWeatherActor(AWeatherActor* Weather)
{
    WeatherActor = Weather;
}

void UTimeSubsystem::Tick(float DeltaTime)
{
    if (!GWorld || GWorld->IsPaused() || !WeatherActor.IsValid())
        return;

    // 推进时间（例如每帧推进 0.04 小时）
    //TimeAccumulator += DeltaTime;
    float TimeStep = DeltaTime * TimeScale;
    TimeOfDay += TimeStep;

    if (TimeOfDay >= 24.0f)
        TimeOfDay -= 24.0f;

    float Day = FMath::GetMappedRangeValueClamped(
        FVector2D(0.f, 24.f),     
        FVector2D(90.f, 450.0f),    
        TimeOfDay                 
    );

    float Night = 360.0f - Day;

    UE_LOG(LogTemp, Warning, TEXT("DeltaTime = %.1f TimeOfDay = %.1f Day = %.1f Night = %.1f"), DeltaTime,TimeOfDay, Day, Night);

    WeatherActor->SetDaytLightRotation(FRotator(Day, 0, 0));
    WeatherActor->SetNightLighRotation(FRotator(Night, 0, 0));

    OnTimeChanged.Broadcast(TimeOfDay);
}