// Copyright Epic Games, Inc. All Rights Reserved.

#include "bansheeGameMode.h"
#include "bansheeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AbansheeGameMode::AbansheeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
