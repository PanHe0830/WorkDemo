// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

/**
 * 
 */

class UMainWidget;

UCLASS()
class WORKDEMO_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
public:
	// 点击I键设置背包的显示或隐藏
	void SetBagVisibility();

	// 点击E键拾取资源
	void PickUpAssert();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainWidget> MainWidget;

	// 主UI实例
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UMainWidget* MainWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	bool bFlag = false;
};
