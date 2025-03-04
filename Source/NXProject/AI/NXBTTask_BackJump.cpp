
#include "AI/NXBTTask_BackJump.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "Player/NXPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UNXBTTask_BackJump::UNXBTTask_BackJump()
{
	NodeName = "BackJump";
}

EBTNodeResult::Type UNXBTTask_BackJump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return EBTNodeResult::Failed;

	ANXBossZombie* AICharacter = Cast< ANXBossZombie>(AIController->GetPawn());
	if (!AICharacter)return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return EBTNodeResult::Failed;

	AICharacter->GetCharacterMovement()->StopMovementImmediately();

	FVector Direction = AICharacter->GetActorLocation() - Player->GetActorLocation();
	Direction.Z = 0;
	Direction.Normalize();

	FVector LaunchVelocity = Direction * 800.0f;
	LaunchVelocity.Z = 300.0f;

	if (USkeletalMeshComponent* MeshComponent = AICharacter->GetMesh())
	{
		if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
		{
			AnimInstance->Montage_Play(AICharacter->BossJumpAnimation, 1.f);
		}
	}

	AICharacter->LaunchCharacter(LaunchVelocity, true,true);

	return EBTNodeResult::Succeeded;
}
