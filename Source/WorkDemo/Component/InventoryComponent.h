// Fill out your copyright notice in the Description page of Project Settings.

/** 
	这是一个背包系统
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorkDemo/Type/ItemData.h"
#include "InventoryComponent.generated.h"

class UAssertResourceManager;
class UBuildSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORKDEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 设置背包的数量 */
	void SetBagMaxSlots(int32 Slots);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSlots = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemData> Items;

	UFUNCTION(BlueprintCallable)
	bool AddItem(int32 ItemID, float Quantity);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int32 ItemID, float Quantity);

	UFUNCTION(BlueprintCallable)
	const TArray<FItemData>& GetItems() const { return Items; }

	void PrintItemsTypeAndNum();

	UPROPERTY()
	UBuildSubsystem* BuildSystem;

	UPROPERTY()
	UAssertResourceManager* AssertResourceManager;
};
