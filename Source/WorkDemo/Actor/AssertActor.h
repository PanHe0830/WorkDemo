// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "WorkDemo/Type/AssertType.h"
#include "AssertActor.generated.h"

class UWidgetComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class WORKDEMO_API AAssertActor : public AActorBase
{
	GENERATED_BODY()
public:
	AAssertActor();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

private:
	bool CheckAssertPosition();

	void SetCurrentAssert();

	void SetWidgetVisibility(bool bFlag);

	void SetWidgetContent();

	UFUNCTION()
	void SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SphereComponentEndOverlag(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Assert")
	TMap<EAssertType, float> AssertAndAssertNum;

	UPROPERTY(EditAnywhere, Category = "Assert")
	int32 MaxAssert = 2; // ��Ҫ���������Դ�Ĵ��� , ���ɵ���Դ���ܻ��ظ�

	UPROPERTY(EditAnywhere, Category = "Assert")
	float MaxAssertNum = 4.0f; // ÿ�����ɵ���Դ���������

	UPROPERTY(EditAnywhere, Category = "Assert")
	TArray<EAssertType> AssertType;

	UPROPERTY(EditAnywhere, Category = "Assert")
	TMap<EAssertType, UStaticMesh*> ResourceMeshMap;

	UPROPERTY(EditAnywhere, Category = "Assert")
	UWidgetComponent* ShowWidget;

	UPROPERTY(EditAnywhere, Category = "Assert")
	USphereComponent* SphereComponent;

public:
	TMap<EAssertType, float> GetAssertNum() { return AssertAndAssertNum; };
};
