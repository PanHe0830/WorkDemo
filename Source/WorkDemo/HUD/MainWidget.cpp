// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "InventoryWidget.h"
#include "WorkDemo/Type/ItemData.h"

void UMainWidget::MenuSetUp()
{
	AddToViewport();/* 将小部件添加到视口 */
	SetVisibility(ESlateVisibility::Visible);/* 设置可见性 */
	bIsFocusable = true;/* 设置聚焦模式 */
}

void UMainWidget::SetBagUiVisibility(ESlateVisibility bflag)
{
	InventoryWidget->SetVisibility(bflag);
}

void UMainWidget::RefreshBagUi(TArray<FItemData> BagAssert)
{
	if (InventoryWidget)
	{
		InventoryWidget->RefreshBagSlots(BagAssert);
	}
}

