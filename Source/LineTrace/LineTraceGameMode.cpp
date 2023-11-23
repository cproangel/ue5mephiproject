// Copyright Epic Games, Inc. All Rights Reserved.

#include "LineTraceGameMode.h"
#include "LineTraceCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALineTraceGameMode::ALineTraceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
