// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorkDemo/Type/ItemData.h"
#include "AssertResourceManager.generated.h"

/**
	������Դ�������
	20250422 -- ��ԴͼƬ
*/

enum class EAssertType : uint8;
struct FStreamableManager;
class AAssertActor;

/**
 * 
 */
UCLASS(Blueprintable)
class WORKDEMO_API UAssertResourceManager : public UObject
{
	GENERATED_BODY()

public:
    // ��Դӳ���
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
    TMap<EAssertType, FAssertSet> AssertIconMap;

    //TMap<EAssertType, TSoftObjectPtr<UTexture2D>> AssertIconMap;

    // ����ö�ٻ�ȡͼƬ��ͬ�����أ�
    UFUNCTION(BlueprintCallable, Category = "Resource")
    UTexture2D* GetIconByType(EAssertType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Resource")
    UStaticMesh* GetMeshByType(EAssertType Type) const;

#if 0
    // �첽���ذ汾����ѡ��
    UFUNCTION(BlueprintCallable, Category = "Resource")
    void LoadIconAsync(EAssertType Type, TFunction<void(UTexture2D*)> Callback);

    // �첽���ع�����
    FStreamableManager StreamableManager;
#endif
};
