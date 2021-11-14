// Copyright Epic Games, Inc. All Rights Reserved.

#include "BobusGameMode.h"
#include "BobusHUD.h"
#include "BobusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABobusGameMode::ABobusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABobusHUD::StaticClass();
}
