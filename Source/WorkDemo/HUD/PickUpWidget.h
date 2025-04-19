// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorkDemo/Type/AssertType.h"
#include "PickUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class WORKDEMO_API UPickUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // 你手动添加的 VerticalBox 变量，需要使用 BindWidget 绑定
    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* ResourceListBox;

    // 用来动态更新资源信息
    UFUNCTION(BlueprintCallable)
    void SetResourceData(const TMap<EAssertType, float>& ResourceData);

    FString GetAssertTypeDisplayName(EAssertType Type);
};
