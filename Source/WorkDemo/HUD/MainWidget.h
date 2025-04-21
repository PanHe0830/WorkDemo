// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UInventoryWidget;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetUp();

	void SetBagUiVisibility(ESlateVisibility bflag);

protected:

private:

	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;

public:
	FORCEINLINE UInventoryWidget* GetInventory() { return InventoryWidget; };
};
