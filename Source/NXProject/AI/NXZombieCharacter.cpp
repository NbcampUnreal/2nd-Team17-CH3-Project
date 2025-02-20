#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXZombieCharacter::ANXZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ANXZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// ANXZombieCharacter는 
	// 레벨에 배치되거나 새롭게 생성(스폰)되면 NXZombieAIController의 빙의가 자동으로 진행됨.

}

void ANXZombieCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);


		GetCharacterMovement()->MaxWalkSpeed = 300.f;


	}
}