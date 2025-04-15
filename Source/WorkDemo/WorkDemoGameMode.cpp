// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorkDemoGameMode.h"
#include "WorkDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWorkDemoGameMode::AWorkDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
