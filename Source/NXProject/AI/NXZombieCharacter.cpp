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
	// ANXZombieCharacter는 
	// 레벨에 배치되거나 새롭게 생성(스폰)되면 NXZombieAIController의 빙의가 자동으로 진행됨.

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
	// 공격 종료 처리
	bIsNowAttacking = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

}

// ANXZombieCharacter.cpp

void ANXZombieCharacter::StartAttack()
{
	BeginAttack();  // BeginAttack을 호출하여 실제 공격 시작
}

void ANXZombieCharacter::BeginAttack()
{
	bIsNowAttacking = false;
	// 공격 시작 로직을 여기에 추가
}

