
#include "AI/BTTask_BossJumpAttack.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "Player/NXPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_BossJumpAttack::UBTTask_BossJumpAttack()
{
	NodeName = "BossJumpAttack";
}

EBTNodeResult::Type UBTTask_BossJumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANXAIController* AIcontroller = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	if (!AIcontroller) return EBTNodeResult::Failed;

	ANXBossZombie* AICharacter = Cast< ANXBossZombie>(AIcontroller->GetPawn());
	if (!AICharacter)return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(!Player) return EBTNodeResult::Failed;

	FVector PlayerLocation = Player->GetActorLocation();
	FVector MyLocation = AICharacter->GetActorLocation();

	FVector TargetLocation = PlayerLocation + Player->GetActorForwardVector() * 100.f;
	TargetLocation.Z += 50.0f;

	FVector LaunchVelocity = (TargetLocation - MyLocation).GetSafeNormal() * 1000.0f;
	LaunchVelocity.Z = 800.0f;

	AICharacter->LaunchCharacter(LaunchVelocity, true, true);


	return EBTNodeResult::Succeeded;
}
