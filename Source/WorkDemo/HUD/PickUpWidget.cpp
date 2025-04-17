// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UPickUpWidget::SetResourceData(const TMap<EAssertType, float>& ResourceData)
{
    if (!ResourceListBox) return;

    ResourceListBox->ClearChildren();

    for (const auto& Elem : ResourceData)
    {
        EAssertType Type = Elem.Key;
        float Amount = Elem.Value;

        //UEnum::GetValueAsString(Type)
        // 创建资源信息文本
        FString ResourceText = FString::Printf(TEXT("%s: %.1f"), *GetAssertTypeDisplayName(Type), Amount);

        UTextBlock* ResourceTextBlock = NewObject<UTextBlock>(this);
        if (ResourceTextBlock)
        {
            ResourceTextBlock->SetText(FText::FromString(ResourceText));
            ResourceListBox->AddChildToVerticalBox(ResourceTextBlock);
        }
    }
}

FString UPickUpWidget::GetAssertTypeDisplayName(EAssertType Type)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAssertType"), true);
    if (!EnumPtr) return TEXT("Invalid");

    return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(Type)).ToString();
}