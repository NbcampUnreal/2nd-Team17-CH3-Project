#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXZombieCharacter::ANXZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ANXZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// ANXZombieCharacter�� 
	// ������ ��ġ�ǰų� ���Ӱ� ����(����)�Ǹ� NXZombieAIController�� ���ǰ� �ڵ����� �����.

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