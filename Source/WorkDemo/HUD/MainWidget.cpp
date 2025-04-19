// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "InventoryWidget.h"

void UMainWidget::MenuSetUp()
{
	AddToViewport();/* ��С������ӵ��ӿ� */
	SetVisibility(ESlateVisibility::Visible);/* ���ÿɼ��� */
	bIsFocusable = true;/* ���þ۽�ģʽ */

	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	APlayerController* PlayerController = World->GetFirstPlayerController();
	//	if (PlayerController)
	//	{
	//		FInputModeUIOnly InputModeData;
	//		InputModeData.SetWidgetToFocus(TakeWidget());/* ����ֻ��ע��С���� */
	//		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);/* ������������� */
	//		PlayerController->SetInputMode(InputModeData);//����ģʽ�����ڽ���
	//		PlayerController->SetShowMouseCursor(true);/* ������� */
	//	}
	//}
}

void UMainWidget::SetBagUiVisibility(ESlateVisibility bflag)
{
	InventoryWidget->SetVisibility(bflag);
}

