// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "InventoryWidget.h"
#include "BuildMenuWidget.h"
#include "WorkDemo/Type/ItemData.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UMainWidget::MenuSetUp()
{
	AddToViewport();/* 将小部件添加到视口 */
	SetVisibility(ESlateVisibility::Visible);/* 设置可见性 */
	bIsFocusable = true;/* 设置聚焦模式 */
}

void UMainWidget::SetBagUiVisibility(ESlateVisibility bflag)
{
	//InventoryWidget->SetVisibility(bflag);
	VerticalBox->SetVisibility(bflag);
	//HorizontalBox->SetVisibility(bflag);
	//ButtonBag->SetVisibility(bflag);
	//ButtonBuild->SetVisibility(bflag);
}

void UMainWidget::RefreshBagUi(TArray<FItemData> BagAssert)
{
	if (InventoryWidget)
	{
		InventoryWidget->RefreshBagSlots(BagAssert);
	}
}

bool UMainWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (ButtonBag)
	{
		ButtonBag->OnClicked.AddDynamic(this, &UMainWidget::BagClick);
	}

	if (ButtonBuild)
	{
		ButtonBuild->OnClicked.AddDynamic(this, &UMainWidget::BuildClick);
	}

	return true;
}

void UMainWidget::BagClick()
{
	if (WidgetSwitcher && InventoryWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("BagClick"));
		WidgetSwitcher->SetActiveWidget(InventoryWidget);
	}
}

void UMainWidget::BuildClick()
{
	if (WidgetSwitcher && BuildMenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("BuildClick"));
		WidgetSwitcher->SetActiveWidget(BuildMenuWidget);
	}
}

