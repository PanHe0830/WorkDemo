// Fill out your copyright notice in the Description page of Project Settings.


#include "BagModelWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 
#include "WorkDemo/Type/AssertType.h"
#include "Components/SizeBox.h"

void UBagModelWidget::NativeConstruct()
{
	AssertImageWidget->SetBrushFromTexture(nullptr,true);
	AssertNum->SetText(FText());
	AssertType = EAssertType::EAT_MAX;

	SizeBox->SetWidthOverride(100.0f);  // ���ÿ��
	SizeBox->SetHeightOverride(100.0f); // ���ø߶�
	
	SizeBoxNum->SetWidthOverride(30.0f);  // ���ÿ��
	SizeBoxNum->SetHeightOverride(30.0f); // ���ø߶�

}

bool UBagModelWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	return true;
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

void UBagModelWidget::SetSize(float Widget, float High)
{
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(Widget);  // ���ÿ��
		SizeBox->SetHeightOverride(High); // ���ø߶�
	}
}