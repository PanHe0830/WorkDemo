#pragma once

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
