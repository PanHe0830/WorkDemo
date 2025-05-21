#pragma once

#include "CoreMinimal.h"
#include "AssertType.generated.h"

UENUM(BlueprintType)
enum class EAssertType : uint8
{
	EAT_Wood UMETA(DisplayName = "Wood"), // ľͷ
	EAT_Gold UMETA(DisplayName = "Gold"), // ���
	EAT_Water UMETA(DisplayName = "Water"), // ˮ
	EAT_Food UMETA(DisplayName = "Food"), // ʳ��
	EAT_Fruit UMETA(DisplayName = "Fruit"), // ˮ��

	EAT_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EBuildType : uint8
{
	EBT_House UMETA(DisplayName = "House"), // ����
	EBT_FarmLand UMETA(DisplayName = "FarmLand"), //ũ��

	EBT_MAX UMETA(DisplayName = "DefaultMAX")
};

// ���ǽ�����Ҫ����Դ�Ľṹ�壬���緿����Ҫľͷ
USTRUCT(BlueprintType)
struct FBuildNeedAssert
{
	GENERATED_BODY()

	// ��������ͼ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BuildBluePrint;

	// ��������ͼ/����
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> BuildTexture;

	// ��������ʱ��Ҫ����Դ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAssertType, float> BuildNeedTypeAndNum;
}; 

UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left UMETA(DisplayName = "Turning Left"),
	ETIP_Right UMETA(DisplayName = "Turning Right"),
	ETIP_NotTurning UMETA(DisplayName = "Not Turning"),

	ETIP_MAX UMETA(DisplayName = "DefaultMAX")
};