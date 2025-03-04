
#include "AI/BTTask_BossJumpAttack.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "Player/NXPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossJumpAttack::UBTTask_BossJumpAttack()
{
	NodeName = "BossJumpAttack";
}

EBTNodeResult::Type UBTTask_BossJumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return EBTNodeResult::Failed;

	ANXBossZombie* AICharacter = Cast< ANXBossZombie>(AIController->GetPawn());
	if (!AICharacter)return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return EBTNodeResult::Failed;

	AICharacter->GetCharacterMovement()->StopMovementImmediately();

	FVector PlayerLocation = Player->GetActorLocation();
	FVector MyLocation = AICharacter->GetActorLocation();

	FVector Direction = (PlayerLocation - MyLocation).GetSafeNormal();
	float Distance = FVector::Dist(PlayerLocation, MyLocation);

	FVector TargetLocation = PlayerLocation - Direction * FMath::Clamp(Distance * 0.3f, 100.0f, 300.0f);
	TargetLocation.Z += 50.0f;

	FVector LaunchVelocity = Direction * FMath::Clamp(Distance * 5.0f, 1200.0f, 1800.0f);
	LaunchVelocity.Z = 900.0f;

	AICharacter->bIsJumpAttacking = true;

	AICharacter->GetCharacterMovement()->GravityScale = 2.0f;

	if (USkeletalMeshComponent* MeshComponent = AICharacter->GetMesh()) 
	{
		if (UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance())
		{
			AnimInstance->Montage_Play(AICharacter->BossJumpAttackAnimation, 1.f);
		}
	}
	FTimerHandle JumpDelayTimer;
	AICharacter->GetWorldTimerManager().SetTimer(
		JumpDelayTimer,
		FTimerDelegate::CreateLambda([AICharacter, LaunchVelocity]()
			{
				if (AICharacter)
				{
					AICharacter->LaunchCharacter(LaunchVelocity, true, true);
				}
			}),
		0.5f,
		false
	);

	AIController->GetBlackboardComponent()->SetValueAsBool("CanJumpAttack", false);

	FTimerHandle CoolDownTimer;
	AICharacter->GetWorldTimerManager().SetTimer(
		CoolDownTimer,
		FTimerDelegate::CreateLambda([AIController]()
			{
				if (AIController)
				{
					AIController->GetBlackboardComponent()->SetValueAsBool("CanJumpAttack", true);
				}
			}),
		6.0f,
		false
	);

	return EBTNodeResult::Succeeded;
}