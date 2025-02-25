
#include "AI/NXNonPlayerCharacter.h"
#include "AI/NXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

ANXNonPlayerCharacter::ANXNonPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ANXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
void ANXNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
}