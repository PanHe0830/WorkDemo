// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "WorkDemo/SubSystem/TimeSubsystem.h"

// Sets default values
AWeatherActor::AWeatherActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DirectionalLightDayTime = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLightDayTime"));
	DirectionalLightDayTime->SetupAttachment(RootComponent);
	DirectionalLightDayTime->SetVisibility(false);

	DirectionalLightNightTime = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLightNightTime"));
	DirectionalLightNightTime->SetupAttachment(RootComponent);
	DirectionalLightNightTime->SetVisibility(false);

	ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
	ExponentialHeightFog->SetupAttachment(RootComponent);

	SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
	SkyAtmosphere->SetupAttachment(RootComponent);
	
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(RootComponent);
	
	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricCloud"));
	VolumetricCloud->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeatherActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetGameInstance())
	{
		UTimeSubsystem* WeatherSubsystem = GetGameInstance()->GetSubsystem<UTimeSubsystem>();
		if (WeatherSubsystem)
		{
			WeatherSubsystem->SetWeatherActor(this);
			WeatherSubsystem->OnTimeChanged.AddDynamic(this , &AWeatherActor::ChangeLightVisibility);
		}
	}
}

// Called every frame
void AWeatherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeatherActor::SetDaytLightRotation(FRotator Rotator)
{
	DirectionalLightDayTime->SetWorldRotation(Rotator);
}

void AWeatherActor::SetNightLighRotation(FRotator Rotator)
{
	DirectionalLightNightTime->SetWorldRotation(Rotator);
}

void AWeatherActor::SetDayLightVisibility()
{
	DirectionalLightDayTime->SetVisibility(true);
	DirectionalLightNightTime->SetVisibility(false);
}

void AWeatherActor::SetNightLightVisibility()
{
	DirectionalLightDayTime->SetVisibility(false);
	DirectionalLightNightTime->SetVisibility(true);
}

void AWeatherActor::ChangeLightVisibility(float Time)
{
	if (Time > 6 && Time < 18)
	{
		SetDayLightVisibility();
	}
	else
	{
		SetNightLightVisibility();
	}
}

