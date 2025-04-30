// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildModeWidget.generated.h"

class UImage;
class UTextBlock;
class USizeBox;
class UButton;

/**
 * 
 */
UCLASS()
class WORKDEMO_API UBuildModeWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
public:
	void SetImage(UTexture2D* Picture);

	void SetText(FText Text);

	void SetCurrentBuildTypeId(int32 TypeId);

private:
	UFUNCTION()
	void BuildFunction();

	UPROPERTY(meta = (BindWidget))
	UImage* ImageShow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AssertShow;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBuild;

	// BuiltType ����������н���������ͣ���int32��������� ����ö���ǲ������ͷ�ļ������鷳
	UPROPERTY(VisibleAnywhere, Category = "BuildMode")
	int32 BuiltType;
};
