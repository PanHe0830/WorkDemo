// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorkDemo/Type/ItemData.h"
#include "WorkDemo/Type/AssertType.h"
#include "AssertResourceManager.generated.h"

/**
	进行资源管理的类
	20250422 -- 资源图片
*/

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
    // 资源映射表
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
    TMap<EAssertType, FAssertSet> AssertIconMap;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resource")
    TMap<EBuildType, FBuildNeedAssert> BuildTypeAndNeed;

    // 根据枚举获取图片（同步加载）
    UFUNCTION(BlueprintCallable, Category = "Resource")
    UTexture2D* GetIconByType(EAssertType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Resource")
    UStaticMesh* GetMeshByType(EAssertType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Resource")
    UTexture2D* GetBuildByType(EBuildType Type) const;

    FORCEINLINE int32 GetBuildTypeAndNeedNum() { return BuildTypeAndNeed.Num(); };

#if 0
    // 异步加载版本（可选）
    UFUNCTION(BlueprintCallable, Category = "Resource")
    void LoadIconAsync(EAssertType Type, TFunction<void(UTexture2D*)> Callback);

    // 异步加载管理器
    FStreamableManager StreamableManager;
#endif
};
