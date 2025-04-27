// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildModeWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBuildModeWidget::SetImage(UTexture2D* Picture)
{
	if (ImageShow)
	{
		ImageShow->SetBrushFromTexture(Picture);
	}
}

void UBuildModeWidget::SetText(FText Text)
{
	if (AssertShow)
	{
		AssertShow->SetText(Text);
	}
}
