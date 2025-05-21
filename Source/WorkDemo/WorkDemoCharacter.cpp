// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorkDemoCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "WorkDemo/Component/MyPlayerMovementComponent.h"
#include "WorkDemo/Component/InventoryComponent.h"
#include "WorkDemo/HUD/InventoryWidget.h"
#include "Animation/AnimMontage.h"
#include "WorkDemo/Component/CombatComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Animation/AnimMontage.h"
#include "WorkDemo.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AWorkDemoCharacter

AWorkDemoCharacter::AWorkDemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block); 
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetNotifyRigidBodyCollision(true); // 启用 Hit 通知事件（非常关键）

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	/** 创建背包组件 */
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	//FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	//FirstCamera->SetupAttachment(GetCapsuleComponent());
	//FirstCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	//FirstCamera->bUsePawnControlRotation = true;

	//Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterFirst"));
	//Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetupAttachment(FirstCamera);
	//Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	CombatComponent->SetIsReplicated(true);
}

void AWorkDemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AWorkDemoCharacter::RecvDamage);
}

void AWorkDemoCharacter::Tick(float DetalTimes)
{
	Super::Tick(DetalTimes);

	HideCharacterIfCameraClose(); // 将第三人称改为第一人称先注释掉判断摄像头和角色网格体之间距离的函数
	AimOffset(DetalTimes);

	//const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("WeaponSocket"));
	//if (HandSocket)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("USkeletalMeshSocket"));
	//	// 获取世界空间下的 Socket 位置
	//	FVector WorldLocation = HandSocket->GetSocketTransform(GetMesh()).GetLocation();
	//
	//	// 绘制调试球
	//	DrawDebugSphere(GetWorld(), WorldLocation, 10.f, 12, FColor::Red, false, 5.f);
	//}
}

void AWorkDemoCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CombatComponent)
	{
		CombatComponent->DemoCharacter = this;
	}
}

void AWorkDemoCharacter::AimOffset(float DetalTimes)
{
	// 角色没有装备武器直接返回
	if (CombatComponent == nullptr || CombatComponent->FirstWeapon == nullptr) return;

	// 获得角色的速度
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	float Speed = Velocity.Size();

	// 获得角色是否在空中
	bool bIsInAir = GetCharacterMovement()->IsFalling();

	if (Speed == 0.f && !bIsInAir) // 角色没有运动并且角色在地面上
	{
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;
		bUseControllerRotationYaw = false;

		//TurnInPlace(DetalTimes);
	}

	if (Speed > 0.f || bIsInAir) // 角色正在运动或在空中
	{
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
	}

	AO_Pitch = GetBaseAimRotation().Pitch;
	if (AO_Pitch > 90.f)
	{
		// map pitch from [270, 360) to [-90, 0)
		FVector2D InRange(270.f, 360.f);
		FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}

void AWorkDemoCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > 90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void AWorkDemoCharacter::RecvDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0)
	{
		// TODO -- 播放死亡动画
		Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("RecvDamage"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWorkDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWorkDemoCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWorkDemoCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWorkDemoCharacter::FireButtonPress);
	//PlayerInputComponent->BindAction("NoFire", IE_Released, this, &AWorkDemoCharacter::FireButtonRelease);
}

void AWorkDemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWorkDemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWorkDemoCharacter::HideCharacterIfCameraClose()
{
	if ((FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
	{
		GetMesh()->SetVisibility(false);
	}
	else
	{
		GetMesh()->SetVisibility(true);
	}
}

void AWorkDemoCharacter::FireButtonPress()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireButtonPress"));
	if (!CombatComponent || CombatComponent->FirstWeapon == nullptr) return;
	CombatComponent->FireButtonPress(true);
}

void AWorkDemoCharacter::FireButtonRelease()
{
	if (!CombatComponent || CombatComponent->FirstWeapon == nullptr) return;

	CombatComponent->FireButtonPress(false);
}

void AWorkDemoCharacter::SetCurrentCanPickUpAssertTypeAndNum(TMap<EAssertType, float>& Assert , AActor* actor)
{
	AssertActor = actor;
	AssertAndAssertNum = Assert;
}

void AWorkDemoCharacter::ClearCurrentCanPickUpAssertTypeAndNum()
{
	AssertActor = nullptr;
	AssertAndAssertNum.Empty();
}

void AWorkDemoCharacter::PickUpCurrentAssertInInventoryComponent()
{
	for (auto& ite : AssertAndAssertNum)
	{
		InventoryComponent->AddItem(static_cast<int32>(ite.Key),ite.Value);
	}
}

void AWorkDemoCharacter::PlayHitTreeMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		if (HitTreeMontage && !AnimInstance->Montage_IsPlaying(HitTreeMontage))
		{
			float MontageSeconds = AnimInstance->Montage_Play(HitTreeMontage);
			UE_LOG(LogTemp, Warning, TEXT("play failed %.1f "), MontageSeconds);
		}
	}
}

void AWorkDemoCharacter::SetCurrentWeapon(AWeaponBase* Weapon)
{
	FirstWeapon = Weapon;
}

bool AWorkDemoCharacter::GetIsEquipWeapon()
{
	return CombatComponent->GetIsEquipWeapon();
}

void AWorkDemoCharacter::SetStartingAimRotation()
{
	StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
}

void AWorkDemoCharacter::PlayFireMontage()
{
	UAnimInstance* Montage = GetMesh()->GetAnimInstance();
	if (FireMontage && Montage)
	{
		Montage->Montage_Play(FireMontage);
	}
}
