#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXZombieCharacter::ANXZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ANXZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// ANXZombieCharacter�� 
	// ������ ��ġ�ǰų� ���Ӱ� �����Ǹ� NXZombieAIController�� ���ǰ� �ڵ����� �����.

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}