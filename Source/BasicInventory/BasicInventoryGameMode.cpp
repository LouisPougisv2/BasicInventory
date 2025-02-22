// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicInventoryGameMode.h"
#include "BasicInventoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasicInventoryGameMode::ABasicInventoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
