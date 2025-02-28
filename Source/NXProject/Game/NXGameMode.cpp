#include "NXGameMode.h"
#include "Player/NXPlayerCharacter.h"
#include "player/NXPlayerController.h"
#include "Game/NXGameState.h"

ANXGameMode::ANXGameMode()
{
	DefaultPawnClass = ANXPlayerCharacter::StaticClass();
	PlayerControllerClass = ANXPlayerController::StaticClass();
	GameStateClass = ANXGameState::StaticClass(); //�츮�� ���� ������Ʈ�� ����
}

