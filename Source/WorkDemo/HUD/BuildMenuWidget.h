// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorkDemo/Type/AssertType.h"
#include "BuildMenuWidget.generated.h"

class UScrollBox;
class UBuildModeWidget;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UBuildMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	FString GetAssertTypeDisplayName(EAssertType Type);

	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TSubclassOf<UBuildModeWidget> BuildModeWidget;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;
};
