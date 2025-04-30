// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChangedSignature, float, TimeOfDay);

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

    /** 实现tick功能需要重写的函数 */
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTimeSubsystem, STATGROUP_Tickables); }
    virtual bool IsTickable() const override { return true; }
    /** 实现tick功能需要重写的函数 */

    float GetTimeOfDay() const { return TimeOfDay; }

    UPROPERTY(BlueprintAssignable, Category = "Time")
    FOnTimeChangedSignature OnTimeChanged;

protected:
    UPROPERTY(EditAnywhere, Category = "Timne" , meta = (ToolTip = "current game time 0.0~24.0 "))
    float TimeOfDay = 6.0f; // 当前游戏小时（0.0~24.0）
    UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "one day real seconds 0.0~24.0 "))
    float DayLengthInRealSeconds = 600.0f; // 一天真实秒数（10分钟一轮）
    UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "time speed 0.0~24.0 "))
    float TimeScale = 24.0f / 600.0f; // 时间推进速度（小时/秒）
    UPROPERTY(EditAnywhere, Category = "Timne", meta = (ToolTip = "speed time 0.0~24.0 "))
    float TimeAccumulator = 0.0f;

};
