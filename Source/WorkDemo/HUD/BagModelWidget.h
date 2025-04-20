// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagModelWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class WORKDEMO_API UBagModelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetImagePicture();

	void SetAssertNum(FText Num);

	UPROPERTY(meta = (BindWidget))
	UImage* AssertImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AssertNum;

	UPROPERTY(meta = (BindWidget))
	UButton* AssertButton;
	
};
