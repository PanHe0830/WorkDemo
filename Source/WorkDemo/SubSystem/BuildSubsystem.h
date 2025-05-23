// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuildSubsystem.generated.h"

class UAssertResourceManager;
class UTestObject;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UBuildSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:
    UPROPERTY(VisibleAnywhere, Category = "AssertManager")
    UAssertResourceManager* ResourceManager;

	void BuildSystemSpawnActor(TSubclassOf<AActor> Actor , FVector Location , FRotator Rotator);

private:
    // 执行碰撞检测
    bool CheckBuildLocation(const FVector& Location, const FRotator& Rotation, const FVector& Extents) const;

    UPROPERTY()
    AActor* PreviewBuilding; // 生成的Actor

    // 建造系统生成Actor函数
    bool BuildSystemSpawnActor(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters SpawnParams);

    // 设置碰撞框的颜色
    void SetCollisionBoxColor();

public:
    void BuildSystemFirstViewCheck(TSubclassOf<AActor> BuildingTemplate, FVector WorldLocation, FVector Direction, TArray<AActor*> IgnoreActors);

public:
    // 生成Actor
    UFUNCTION(BlueprintCallable, Category = "Build System")
    bool ShowPreview(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation);

    //销毁Actor
    UFUNCTION(BlueprintCallable, Category = "Build System")
    void DestoryCurrentActor();

    // 改变Actor的位置
    UFUNCTION(BlueprintCallable, Category = "Build System")
    void ChangePreviewActorPosition(FVector position);

    // 设置碰撞框在游戏中的可见性
    void SetCollisionBoxVisibilityHide();

    // 获得当前的位置是否合适
    bool GetCurrentIsRight();

    // 进行盒体检测判断当前位置是否合适
    bool DoBoxCheck();

    // 设置actor的碰撞
    void SetActorColliksion();

    // 记录Actor的位置
    UPROPERTY(VisibleAnywhere, Category = "Build System")
    FVector SpawnLocation;
};
