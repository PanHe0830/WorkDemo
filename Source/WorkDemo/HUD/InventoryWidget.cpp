// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "BagModelWidget.h" // 你自定义的格子Widget类

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

    if (!ItemSlotWidgetClass || !UniformGridPanel) return;
    
    for (int32 Index = 0; Index < SlotCount; ++Index)
    {
        UBagModelWidget* NewSlot = CreateWidget<UBagModelWidget>(this, ItemSlotWidgetClass);
        if (NewSlot)
        {
            UUniformGridSlot* GridSlot = UniformGridPanel->AddChildToUniformGrid(NewSlot);
            GridSlot->SetRow(Index / Columns);
            GridSlot->SetColumn(Index % Columns);
        }
    }
}