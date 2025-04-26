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
    // ִ����ײ���
    bool CheckBuildLocation(const FVector& Location, const FRotator& Rotation, const FVector& Extents) const;

    UPROPERTY()
    AActor* PreviewBuilding; // ���ɵ�Actor

    // ����ϵͳ����Actor����
    bool BuildSystemSpawnActor(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters SpawnParams);

    // ������ײ�����ɫ
    void SetCollisionBoxColor();

public:
    // ����Actor
    UFUNCTION(BlueprintCallable, Category = "Build System")
    bool ShowPreview(TSubclassOf<AActor> BuildingTemplate, const FVector& Location, const FRotator& Rotation);

    //����Actor
    UFUNCTION(BlueprintCallable, Category = "Build System")
    void DestoryCurrentActor();

    // �ı�Actor��λ��
    UFUNCTION(BlueprintCallable, Category = "Build System")
    void ChangePreviewActorPosition(FVector position);

    // ������ײ������Ϸ�еĿɼ���
    void SetCollisionBoxVisibilityHide();

    // ��õ�ǰ��λ���Ƿ����
    bool GetCurrentIsRight();

    // ��¼Actor��λ��
    UPROPERTY(VisibleAnywhere, Category = "Build System")
    FVector SpawnLocation;
};
