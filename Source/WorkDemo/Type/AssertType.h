#pragma once

#include "CoreMinimal.h"
#include "AssertType.generated.h"

UENUM(BlueprintType)
enum class EAssertType : uint8
{
	EAT_Wood UMETA(DisplayName = "Wood"), // 木头
	EAT_Gold UMETA(DisplayName = "Gold"), // 金块
	EAT_Water UMETA(DisplayName = "Water"), // 水
	EAT_Food UMETA(DisplayName = "Food"), // 食物
	EAT_Fruit UMETA(DisplayName = "Fruit"), // 水果

	EAT_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EBuildType : uint8
{
	EBT_House UMETA(DisplayName = "House"), // 房子
	EBT_FarmLand UMETA(DisplayName = "FarmLand"), //农田

	EBT_MAX UMETA(DisplayName = "DefaultMAX")
};

// 这是建筑需要的资源的结构体，例如房子需要木头
USTRUCT(BlueprintType)
struct FBuildNeedAssert
{
	GENERATED_BODY()

	// 建筑的蓝图
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BuildBluePrint;

	// 建筑的贴图/纹理
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> BuildTexture;

	// 建筑建造时需要的资源
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