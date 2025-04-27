// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenuWidget.h"
#include "BuildModeWidget.h"
#include "Components/ScrollBox.h"
#include "WorkDemo/SubSystem/BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"

void UBuildMenuWidget::NativeConstruct()
{
	UBuildSubsystem* BuildSystem = GetWorld()->GetGameInstance()->GetSubsystem<UBuildSubsystem>();
	if (BuildSystem)
	{
		auto BuildMap = BuildSystem->ResourceManager->BuildTypeAndNeed;

		for (int32 i = 0; i < BuildMap.Num(); i++)
		{
			UBuildModeWidget* ChildBuild = CreateWidget<UBuildModeWidget>(this,BuildModeWidget);
			if (ChildBuild)
			{

				//ScrollBox->AddChild();
			}
		}
	}
}
