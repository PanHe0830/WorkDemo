// Fill out your copyright notice in the Description page of Project Settings.


#include "AssertResourceManager.h"
#include "UObject/Object.h"
#include "WorkDemo/Type/AssertType.h"
#include "Engine/StreamableManager.h" // ��� StreamableManager ֧��

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
        // ������Դ�������б�
        TArray<FSoftObjectPath> PathsToLoad;
        PathsToLoad.Add(AssertIconMap[Type].ToSoftObjectPath());

        // �첽������Դ
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