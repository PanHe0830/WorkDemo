// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "InventoryWidget.h"

void UMainWidget::MenuSetUp()
{
	AddToViewport();/* 将小部件添加到视口 */
	SetVisibility(ESlateVisibility::Visible);/* 设置可见性 */
	bIsFocusable = true;/* 设置聚焦模式 */

	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	APlayerController* PlayerController = World->GetFirstPlayerController();
	//	if (PlayerController)
	//	{
	//		FInputModeUIOnly InputModeData;
	//		InputModeData.SetWidgetToFocus(TakeWidget());/* 设置只关注与小部件 */
	//		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);/* 设置鼠标光标锁定 */
	//		PlayerController->SetInputMode(InputModeData);//设置模式集中于界面
	//		PlayerController->SetShowMouseCursor(true);/* 看到光标 */
	//	}
	//}
}

void UMainWidget::SetBagUiVisibility(ESlateVisibility bflag)
{
	InventoryWidget->SetVisibility(bflag);
}

