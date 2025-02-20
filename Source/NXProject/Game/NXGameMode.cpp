#include "NXGameMode.h"
#include "Player/NXPlayerCharacter.h"
#include "player/NXPlayerController.h"

ANXGameMode::ANXGameMode()
{
	DefaultPawnClass = ANXPlayerCharacter::StaticClass();
	PlayerControllerClass = ANXPlayerController::StaticClass();
}

