// Copyright Epic Games, Inc. All Rights Reserved.

#include "BobusGameMode.h"
#include "UI/BobusHUD.h"
#include "Characters/BobusCharacterBase.h"
#include "UObject/ConstructorHelpers.h"

ABobusGameMode::ABobusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_BobusCharacterPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABobusHUD::StaticClass();
}
