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
	ACharacterPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	void ChangeActorLocation(float XY);

	void MouseLeftClicked();

public:
	// ���I�����ñ�������ʾ������
	void SetBagVisibility();

	// ���E��ʰȡ��Դ
	void PickUpAssert();

	// �����������������
	void DamageTree();

	// ˢ�±�������
	void RefreshUi();

	// ȷ��������Դ
	bool CheckAssertDown();

	// ��ʼ�������� �� �����ǽ������͵�int32��ֵ
	void BeginBuild(int32 TypeId);

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainWidget> MainWidget;

	// ��UIʵ��
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UMainWidget* MainWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	bool bFlag = false;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float CurrentDamage = 50.f;

	bool bBuildFlag = true;
	//int32 id;
};
