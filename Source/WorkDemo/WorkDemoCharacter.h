// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WorkDemo/Type/AssertType.h"
#include "WorkDemoCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UMyPlayerMovementComponent;
class UInventoryComponent;
class UInventoryWidget;
class UAnimMontage;
class UCombatComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AWorkDemoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** First camera add by ph */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//UCameraComponent* FirstCamera;

	/** First Skeletal add by ph */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//USkeletalMeshComponent* Mesh1P;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** MyCharacterMoveComponet */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UMyPlayerMovementComponent* MoveComponent;

public:
	AWorkDemoCharacter();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DetalTimes) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** GetBagComponent **/
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; };
	/** add by ph */
	//FORCEINLINE USkeletalMeshComponent* GetFirstSkeleMesh() { return Mesh1P; };

private:
	/** 当角色靠近障碍物时摄像机在角色非常近的地方时将角色设置为不可见 */
	void HideCharacterIfCameraClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	/** 角色背包组件 */
	UPROPERTY(EditAnywhere, Category = "Component")
	UInventoryComponent* InventoryComponent;

	/** 角色战斗组件 */
	UCombatComponent* CombatComponent;

	/* Animation */
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* HitTreeMontage;

public:
	/** 记录当前角色可以拿到那些物品 */
	void SetCurrentCanPickUpAssertTypeAndNum(TMap<EAssertType, float>& Assert , AActor* actor);	// 设置当前的物品类型和数量

	void ClearCurrentCanPickUpAssertTypeAndNum();// 清空当前的物品类型和数量

	void PickUpCurrentAssertInInventoryComponent();

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	TMap<EAssertType, float> AssertAndAssertNum;

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	AActor* AssertActor;

	/* Play Animation */
	void PlayHitTreeMontage();
};

