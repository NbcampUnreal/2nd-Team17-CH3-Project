
#include "AI/NXNonPlayerCharacter.h"
#include "AI/NXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXNonPlayerCharacter::ANXNonPlayerCharacter()
{
	AIControllerClass = ANXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WalkSpeed = 80.f;
	RunSpeed = 300.f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
