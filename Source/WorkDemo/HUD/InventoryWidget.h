// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UBagModelWidget;
/**
 * 
 */
UCLASS()
class WORKDEMO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* UniformGridPanel;

    UPROPERTY(EditDefaultsOnly, Category = "Backpack")
    TSubclassOf<UBagModelWidget> ItemSlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Backpack")
    int32 SlotCount = 30;

    UPROPERTY(EditDefaultsOnly, Category = "Backpack")
    int32 Columns = 6;  // Ã¿ÐÐ 6 ¸ö
};
