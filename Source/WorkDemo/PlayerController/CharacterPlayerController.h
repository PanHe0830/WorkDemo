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
	// 点击I键设置背包的显示或隐藏
	void SetBagVisibility();

	// 点击E键拾取资源
	void PickUpAssert();

	// 点击鼠标左键砍树操作
	void DamageTree();

	// 刷新背包界面
	void RefreshUi();

	// 确认消耗资源
	bool CheckAssertDown();

	// 开始建造流程 ， 参数是建筑类型的int32的值
	void BeginBuild(int32 TypeId);

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainWidget> MainWidget;

	// 主UI实例
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UMainWidget* MainWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	bool bFlag = false;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float CurrentDamage = 50.f;

	bool bBuildFlag = true;
	//int32 id;
};
