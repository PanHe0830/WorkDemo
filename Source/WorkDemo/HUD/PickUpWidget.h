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
    // ���ֶ���ӵ� VerticalBox ��������Ҫʹ�� BindWidget ��
    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* ResourceListBox;

    // ������̬������Դ��Ϣ
    UFUNCTION(BlueprintCallable)
    void SetResourceData(const TMap<EAssertType, float>& ResourceData);

    FString GetAssertTypeDisplayName(EAssertType Type);
};
