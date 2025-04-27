// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UInventoryWidget;
class UBuildMenuWidget;
struct FItemData;
class UVerticalBox;
class UHorizontalBox;
class UButton;
class UWidgetSwitcher;

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
	virtual bool Initialize() override;

	UFUNCTION()
	void BagClick();

	UFUNCTION()
	void BuildClick();

private:

	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	UBuildMenuWidget* BuildMenuWidget;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBag;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBuild;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	

public:
	FORCEINLINE UInventoryWidget* GetInventory() { return InventoryWidget; };
};
