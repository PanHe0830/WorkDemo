// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildHouse.h"
#include "Components/WidgetComponent.h"
#include "WorkDemo/HUD/BuildWidget.h"
#include "Kismet/GameplayStatics.h"

void ABuildHouse::BeginPlay()
{
	Super::BeginPlay();

	UBuildWidget* BuildWidget = Cast<UBuildWidget>(WidgetComponent->GetUserWidgetObject());
	if (BuildWidget)
	{
		BuildWidget->SetWidgetOwner(this);
	}

	//WidgetComponent->SetVisibility(false);
}

void ABuildHouse::NotifyActorBeginCursorOver()
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyActorBeginCursorOver"));
	Super::NotifyActorBeginCursorOver();
}

void ABuildHouse::NotifyActorEndCursorOver()
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyActorEndCursorOver"));
	Super::NotifyActorEndCursorOver();
}

void ABuildHouse::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (WidgetComponent)
	{
		if (!bflag)
		{
			WidgetComponent->SetVisibility(true);

			UE_LOG(LogTemp, Warning, TEXT("NotifyActorOnClicked"));
		}
		else
		{
			WidgetComponent->SetVisibility(false);

			UE_LOG(LogTemp, Warning, TEXT("NotifyActorOnClicked"));
		}
	}

	bflag = !bflag;
}

void ABuildHouse::Destroyed()
{
	Super::Destroyed();

	UE_LOG(LogTemp, Warning, TEXT("ABuildHouse is destroyed"));
}
