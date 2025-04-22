// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertResourceManager.h"
#include "UObject/Object.h"
#include "WorkDemo/Type/AssertType.h"
#include "Engine/StreamableManager.h" // 添加 StreamableManager 支持

UTexture2D* UAssertResourceManager::GetIconByType(EAssertType Type) const
{
    if (AssertIconMap.Contains(Type))
    {
        return AssertIconMap[Type].LoadSynchronous();
    }
    return nullptr;
}

#if 0
void UAssertResourceManager::LoadIconAsync(EAssertType Type, TFunction<void(UTexture2D*)> Callback)
{
    if (AssertIconMap.Contains(Type))
    {
        // 构建资源软引用列表
        TArray<FSoftObjectPath> PathsToLoad;
        PathsToLoad.Add(AssertIconMap[Type].ToSoftObjectPath());

        // 异步加载资源
        StreamableManager.RequestAsyncLoad(
            PathsToLoad,
            FStreamableDelegate::CreateLambda([this, Type, Callback]()
                {
                    if (UTexture2D* Icon = AssertIconMap[Type].Get())
                    {
                        Callback(Icon);
                    }
                    else
                    {
                        Callback(nullptr);
                    }
                }
            ));
    }
    else
    {
        Callback(nullptr);
    }
}

#endif