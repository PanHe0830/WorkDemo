// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagModelWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
class USizeBox;

enum class EAssertType : uint8;
/**
 * 
 */
UCLASS()
class WORKDEMO_API UBagModelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetImagePicture(UTexture2D* AssertImage);

	void SetAssertNum(FText Num);

	void SetAssertType(EAssertType type);

	void SetSize(float Widget , float High);

	UPROPERTY(meta = (BindWidget))
	UImage* AssertImageWidget;

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	UTexture2D* AssertTexture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AssertNum;

	UPROPERTY(meta = (BindWidget))
	UButton* AssertButton;
	
	UPROPERTY(VisibleAnywhere, Category = "Assert")
	EAssertType AssertType;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBoxNum;
	
};
