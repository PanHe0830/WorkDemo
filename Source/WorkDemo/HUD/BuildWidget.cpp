// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildWidget.h"
#include "Components/Button.h"

bool UBuildWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (ButtonDestory)
	{
		ButtonDestory->OnClicked.AddDynamic(this, &UBuildWidget::DestroyAttachActor);
	}
	
	SetVisibility(ESlateVisibility::Hidden);

	return true;
}

void UBuildWidget::DestroyAttachActor()
{
	UE_LOG(LogTemp, Warning, TEXT("DestroyAttachActor"));

	if (BuildActor)
	{
		BuildActor->Destroy();
	}
}

void UBuildWidget::SetWidgetOwner(AActor* Actor)
{
	BuildActor = Actor;
}
