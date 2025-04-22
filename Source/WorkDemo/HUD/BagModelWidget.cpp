// Fill out your copyright notice in the Description page of Project Settings.


#include "BagModelWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 
#include "WorkDemo/Type/AssertType.h"

void UBagModelWidget::NativeConstruct()
{
	AssertImageWidget->SetBrushFromTexture(nullptr,true);
	AssertNum->SetText(FText());
	AssertType = EAssertType::EAT_MAX;
}

void UBagModelWidget::SetImagePicture(UTexture2D* AssertImage)
{
	AssertImageWidget->SetBrushFromTexture(AssertImage, true);
}

void UBagModelWidget::SetAssertNum(FText Num)
{
	AssertNum->SetText(Num);
}

void UBagModelWidget::SetAssertType(EAssertType type)
{
	AssertType = type;
}
