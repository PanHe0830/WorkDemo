// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChangedSignature, float, TimeOfDay);

class UCurveFloat;
class AWeatherActor;

/**
 * 
 */
UCLASS(Blueprintable)
class WORKDEMO_API UTimeSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void SetWeatherActor(AWeatherActor* Weather);

    /** 实现tick功能需要重写的函数 */
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTimeSubsystem, STATGROUP_Tickables); }
    virtual bool IsTickable() const override { return true; }
    /** 实现tick功能需要重写的函数 */

    float GetTimeOfDay() const { return TimeOfDay; }

    UPROPERTY(BlueprintAssignable, Category = "Time")
    FOnTimeChangedSignature OnTimeChanged;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Time")
    TWeakObjectPtr<AWeatherActor> WeatherActor;

    UPROPERTY(EditAnywhere, Category = "Timne" , meta = (ToolTip = "current game time 0.0~24.0 "))
    float TimeOfDay = 18.0f; // 当前游戏小时（0.0~24.0）

    //UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "one day real seconds 0.0~24.0 "))
    //float DayLengthInRealSecond = 600.0f; // 一天真实秒数 (600s一天)
    //UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "time speed 0.0~24.0 "))
    //float TimeScale = 24.0f / DayLengthInRealSecond; // 时间推进速度（h/s）
    
    UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "h/s one seconds go hours 1 - 24 "))
    float TimeScale = 1.0f; // 时间推进速度（h/s） 一秒钟推进几个小时

    //UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "speed time 0.0~24.0 "))
    //float TimeAccumulator = 0.0f;

    //UPROPERTY(EditAnywhere, Category = "Time")
    //UCurveFloat* curve;
};

/* 180 - 360 白天 */
/* 0 -180 黑天 */