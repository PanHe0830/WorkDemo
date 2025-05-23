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
class AWeaponBase;

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

	/** add by ph */
	virtual void PostInitializeComponents() override;

	// 计算角色偏移用于装备武器动画
	void AimOffset(float DetalTimes);

	void TurnInPlace(float DeltaTime);

	ETurningInPlace TurningInPlace;

	UFUNCTION()
	void RecvDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** GetBagComponent **/
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; };
	/** add by ph */
	//FORCEINLINE USkeletalMeshComponent* GetFirstSkeleMesh() { return Mesh1P; };

	FORCEINLINE UCombatComponent* GetCombatComponent() { return CombatComponent; };

	FORCEINLINE float GetAO_Yaw() { return AO_Yaw; };
	FORCEINLINE float GetAO_Pitch() { return AO_Pitch; };

public:
	/* Play Animation */
	void PlayFireMontage(); // 播放开火动画
	void PlayHitTreeMontage(); // 播放砍树动画

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

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	UPROPERTY(EditAnywhere, Category = "Fire")
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, Category = "Character")
	float Health = 100.f;

public:
	// 武器开火
	void FireButtonPress();

	// 停止开火
	void FireButtonRelease();

	/** 记录当前角色可以拿到那些物品 */
	void SetCurrentCanPickUpAssertTypeAndNum(TMap<EAssertType, float>& Assert , AActor* actor);	// 设置当前的物品类型和数量

	void ClearCurrentCanPickUpAssertTypeAndNum();// 清空当前的物品类型和数量

	void PickUpCurrentAssertInInventoryComponent();

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	TMap<EAssertType, float> AssertAndAssertNum;

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	AActor* AssertActor; // 资源Actor

	/** 角色当前持有的武器 */
	void SetCurrentWeapon(AWeaponBase* Weapon);

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeaponBase* FirstWeapon;

	bool GetIsEquipWeapon(); // 是否装备武器

	void SetStartingAimRotation(); // 设置刚开始角色拾取武器后，角色控制器的Yaw
};

