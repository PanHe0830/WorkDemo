// Fill out your copyright notice in the Description page of Project Settings.


#include "BagModelWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h" 

void UBagModelWidget::SetImagePicture()
{
	//AssertImage->texture;
}

void UBagModelWidget::SetAssertNum(FText Num)
{
	AssertNum->SetText(Num);
}
