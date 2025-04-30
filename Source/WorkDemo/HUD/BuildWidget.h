// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UBuildWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void DestroyAttachActor();

	UPROPERTY(VisibleAnywhere, Category = "Build")
	AActor* BuildActor = nullptr;
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonDestory;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonCollection;

public:
	void SetWidgetOwner(AActor* Actor);
};
