// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherActor.generated.h"

class UDirectionalLightComponent;
class UExponentialHeightFogComponent;
class USkyAtmosphereComponent;
class USkyLightComponent;
class UVolumetricCloudComponent;

UCLASS()
class WORKDEMO_API AWeatherActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDaytLightRotation(FRotator Rotator);

	void SetNightLighRotation(FRotator Rotator);

	void SetDayLightVisibility();

	void SetNightLightVisibility();

	UFUNCTION()
	void ChangeLightVisibility(float Time);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weather")
	UDirectionalLightComponent* DirectionalLightDayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	UDirectionalLightComponent* DirectionalLightNightTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	UExponentialHeightFogComponent* ExponentialHeightFog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	USkyLightComponent* SkyLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	UVolumetricCloudComponent* VolumetricCloud;
};
