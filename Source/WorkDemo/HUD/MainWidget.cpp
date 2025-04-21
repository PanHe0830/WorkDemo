// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "InventoryWidget.h"

void UMainWidget::MenuSetUp()
{
	AddToViewport();/* ��С������ӵ��ӿ� */
	SetVisibility(ESlateVisibility::Visible);/* ���ÿɼ��� */
	bIsFocusable = true;/* ���þ۽�ģʽ */
}

void UMainWidget::SetBagUiVisibility(ESlateVisibility bflag)
{
	InventoryWidget->SetVisibility(bflag);
}

