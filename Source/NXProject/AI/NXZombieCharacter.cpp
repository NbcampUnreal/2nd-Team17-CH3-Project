#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXZombieCharacter::ANXZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ANXZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// ANXZombieCharacter는 
	// 레벨에 배치되거나 새롭게 생성되면 NXZombieAIController의 빙의가 자동으로 진행됨.

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}