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
	void SetBagVisibility();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainWidget> MainWidget;

	// Ö÷UIÊµÀý
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UMainWidget* MainWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	bool bFlag = false;
};
