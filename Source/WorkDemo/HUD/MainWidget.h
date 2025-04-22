// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UInventoryWidget;
struct FItemData;

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

	void RefreshBagUi(TArray<FItemData> BagAssert);

protected:

private:

	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;

public:
	FORCEINLINE UInventoryWidget* GetInventory() { return InventoryWidget; };
};
