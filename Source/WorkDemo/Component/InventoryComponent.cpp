// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

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
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(int32 ItemID, int32 Quantity)
{
    for (FItemData& Slot : Items)
    {
        if (Slot.ItemID == ItemID && Slot.Quantity < Slot.MaxStackSize)
        {
            int32 AddAmount = FMath::Min(Slot.MaxStackSize - Slot.Quantity, Quantity);
            Slot.Quantity += AddAmount;
            Quantity -= AddAmount;
            if (Quantity <= 0) return true;
        }
    }

    for (FItemData& Slot : Items)
    {
        if (!Slot.IsValid())
        {
            Slot.ItemID = ItemID;
            Slot.Quantity = FMath::Min(Quantity, 99);
            Slot.MaxStackSize = 99;
            Quantity -= Slot.Quantity;
            if (Quantity <= 0) return true;
        }
    }

    return false;
}

bool UInventoryComponent::RemoveItem(int32 ItemID, int32 Quantity)
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

