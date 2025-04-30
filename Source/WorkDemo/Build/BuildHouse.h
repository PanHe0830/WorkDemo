// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildBase.h"
#include "BuildHouse.generated.h"

/**
 * 
 */
UCLASS()
class WORKDEMO_API ABuildHouse : public ABuildBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginCursorOver() override;

	virtual void NotifyActorEndCursorOver() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	virtual void Destroyed() override;

	bool bflag = false;
};
