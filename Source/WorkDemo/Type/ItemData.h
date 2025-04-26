#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemID = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Quantity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStackSize = 999.f;

    UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
    UTexture2D* AssertTexture = nullptr;
    
    bool IsValid() const { return ItemID != -1; }
};

// ����ṹ���ǹ���ĳ����Դ�������Դ������ľͷ��Դ��ľͷ����ͼ��ľͷ��������
USTRUCT(BlueprintType)
struct FAssertSet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> AssertTexture = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> AssertMesh = nullptr;
};