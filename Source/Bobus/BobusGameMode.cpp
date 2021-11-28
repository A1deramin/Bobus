#include "BobusGameMode.h"
#include "Player/BobusPlayerState.h"
#include "UI/BobusHUD.h"
#include "Characters/BobusCharacterBase.h"
#include "UObject/ConstructorHelpers.h"

ABobusGameMode::ABobusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Characters/BP_BobusCharacterPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerStateClass = ConstructorHelpers::FClassFinder<APlayerState>(TEXT("/Game/FirstPersonCPP/Blueprints/BP_BobusPlayerState")).Class;

	// use our custom HUD class
	HUDClass = ABobusHUD::StaticClass();
}
