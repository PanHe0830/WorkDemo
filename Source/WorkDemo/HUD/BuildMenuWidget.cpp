// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenuWidget.h"
#include "BuildModeWidget.h"
#include "Components/ScrollBox.h"
#include "WorkDemo/SubSystem/BuildSubsystem.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"

void UBuildMenuWidget::NativeConstruct()
{
	UBuildSubsystem* BuildSystem = GetWorld()->GetGameInstance()->GetSubsystem<UBuildSubsystem>();
	if (BuildSystem && BuildModeWidget)
	{
		UAssertResourceManager* Manager = BuildSystem->ResourceManager;
		if (Manager)
		{
			auto BuildMap = Manager->BuildTypeAndNeed;

			for (auto& ite : BuildMap)
			{
				UBuildModeWidget* ChildBuild = CreateWidget<UBuildModeWidget>(this, BuildModeWidget);
				if (ChildBuild)
				{
					ChildBuild->SetImage(Manager->GetBuildByType(ite.Key));
					for (auto& itee : ite.Value.BuildNeedTypeAndNum)
					{
						FString Text = FString::Printf(TEXT("%s : %.1f"), *GetAssertTypeDisplayName(itee.Key), itee.Value);
						ChildBuild->SetText(FText::FromString(Text));
					}

					ScrollBox->AddChild(ChildBuild);
				}
			}
		}
	}
}

FString UBuildMenuWidget::GetAssertTypeDisplayName(EAssertType Type)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAssertType"), true);
	if (!EnumPtr) return TEXT("Invalid");

	return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(Type)).ToString();
}
