#pragma once

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
