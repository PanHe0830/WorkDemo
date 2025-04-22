// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "WorkDemo/ResourceManager/AssertResourceManager.h"
#include "WorkDemo/Type/AssertType.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
    Items.SetNum(MaxSlots);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    //ResourceManager = NewObject<UAssertResourceManager>();
    ResourceManager = LoadObject<UAssertResourceManager>(nullptr, TEXT("BluePrint/ResourceManager/BP_AssertResourceManager"));
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SetBagMaxSlots(int32 Slots)
{
    Items.SetNum(Slots);
}

bool UInventoryComponent::AddItem(int32 ItemID, float Quantity)
{
    for (FItemData& ite : Items)
    {
        //UE_LOG(LogTemp , Warning , TEXT("first for %d"),Items.Num());
        if (ItemID == ite.ItemID && ite.Quantity < ite.MaxStackSize)
        {
            float AddCount = FMath::Min(ite.MaxStackSize - ite.Quantity, Quantity);
            ite.Quantity += AddCount;
            return true;
        }
    }

    for (FItemData& ite : Items)
    {
        //UE_LOG(LogTemp, Warning, TEXT("second for %d"), Items.Num());
        if (!ite.IsValid())
        {
            ite.ItemID = ItemID;
            ite.Quantity = FMath::Min(Quantity, 999.f);
            ite.MaxStackSize = 999.f;
            if (ResourceManager)
            {
                ite.AssertTexture = ResourceManager->GetIconByType(static_cast<EAssertType>(ItemID));
            }
            return true;
        }
    }

    return false;
}

bool UInventoryComponent::RemoveItem(int32 ItemID, float Quantity)
{
    for (FItemData& Slot : Items)
    {
        if (Slot.ItemID == ItemID)
        {
            if (Slot.Quantity >= Quantity)
            {
                Slot.Quantity -= Quantity;
                if (Slot.Quantity == 0) Slot = FItemData(); // ÷ÿ÷√ø’Œª
                return true;
            }
        }
    }
    return false;
}

void UInventoryComponent::PrintItemsTypeAndNum()
{
    for (auto& ite : Items)
    {
        UE_LOG(LogTemp , Warning , TEXT("%d: %f") , ite.ItemID , ite.Quantity);
    }
}