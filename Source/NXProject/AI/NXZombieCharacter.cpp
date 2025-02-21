#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/Animation/NXZombieAnimInstance.h"


ANXZombieCharacter::ANXZombieCharacter()
	:bIsNowAttacking(false)
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

	UNXZombieAnimInstance* AnimInstance = Cast<UNXZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(AnimInstance) == true)
	{
		AnimInstance->OnCheckHit.AddDynamic(this, &ANXZombieCharacter::OnCheckHit);

	}

	if (false == IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
		GetCharacterMovement()->MaxWalkSpeed = 300.f;

	}
}

void ANXZombieCharacter::OnCheckHit()
{
	UKismetSystemLibrary::PrintString(this, TEXT("OnCheckHit()"));
}


void ANXZombieCharacter::EndAttack(UAnimMontage* InMontage, bool bInterrupted)
{
	// ���� ���� ó��
	bIsNowAttacking = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

}

// ANXZombieCharacter.cpp

void ANXZombieCharacter::StartAttack()
{
	BeginAttack();  // BeginAttack�� ȣ���Ͽ� ���� ���� ����
}

void ANXZombieCharacter::BeginAttack()
{
	bIsNowAttacking = false;
	// ���� ���� ������ ���⿡ �߰�
}

