// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "BagModelWidget.h" // 你自定义的格子Widget类
#include "WorkDemo/Type/ItemData.h"

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //if (!ItemSlotWidgetClass || !WrapBox) return;
    //
    //for (int32 Index = 0; Index < SlotCount; ++Index)
    //{
    //    UBagModelWidget* NewSlot = CreateWidget<UBagModelWidget>(this, ItemSlotWidgetClass);
    //    if (NewSlot)
    //    {
    //        UWrapBoxSlot* WrapSlot = WrapBox->AddChildToWrapBox(NewSlot);
    //    }
    //}

    BagArray.Empty();

    if (!ItemSlotWidgetClass || !UniformGridPanel) return;
    
    for (int32 Index = 0; Index < SlotCount; ++Index)
    {
        UBagModelWidget* NewSlot = CreateWidget<UBagModelWidget>(this, ItemSlotWidgetClass);
        if (NewSlot)
        {
            UUniformGridSlot* GridSlot = UniformGridPanel->AddChildToUniformGrid(NewSlot);
            GridSlot->SetRow(Index / Columns);
            GridSlot->SetColumn(Index % Columns);
            BagArray.Add(NewSlot);
        }
    }
}

void UInventoryWidget::RefreshBagSlots(TArray<FItemData> BagAssert)
{
    if (BagArray.Num() != BagAssert.Num()) return;

    int32 BagNum = BagArray.Num();
    for (int32 Bag = 0; Bag < BagNum; Bag++)
    {
        BagArray[Bag]->SetImagePicture(BagAssert[Bag].AssertTexture);
        BagArray[Bag]->SetAssertNum(FText::FromString(FString::Printf(TEXT("%.2f"), BagAssert[Bag].Quantity)));
    }
}
