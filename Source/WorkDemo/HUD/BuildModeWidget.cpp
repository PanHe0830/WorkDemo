// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildModeWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "WorkDemo/PlayerController/CharacterPlayerController.h"
#include "Components/Button.h"

bool UBuildModeWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	SizeBox->SetWidthOverride(300.f);
	SizeBox->SetHeightOverride(200.f);


	if (ButtonBuild)
	{
		ButtonBuild->OnClicked.AddDynamic(this, &UBuildModeWidget::BuildFunction);
	}

	return true;
}

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

void UBuildModeWidget::SetCurrentBuildTypeId(int32 TypeId)
{
	BuiltType = TypeId;
}

void UBuildModeWidget::BuildFunction()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ACharacterPlayerController* PlayerController = Cast<ACharacterPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		if (PlayerController)
		{
			PlayerController->BeginBuild(BuiltType);
		}
	}
}
