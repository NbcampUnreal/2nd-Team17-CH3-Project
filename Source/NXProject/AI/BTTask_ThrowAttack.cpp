#include "AI/BTTask_ThrowAttack.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "AI/Stone.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NXPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ThrowAttack::UBTTask_ThrowAttack()
{
	NodeName = "ThrowAttack";
}

EBTNodeResult::Type UBTTask_ThrowAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return EBTNodeResult::Failed;

	ANXBossZombie* AICharacter = Cast< ANXBossZombie>(AIController->GetPawn());
	if (!AICharacter)return EBTNodeResult::Failed;

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return EBTNodeResult::Failed;

	FVector SpawnLocation = AICharacter->GetActorLocation()+(AICharacter->GetActorForwardVector() * 100.0f) + FVector(0, 0, 50.0f);
	FRotator SpawnRotation = (Player->GetActorLocation() - SpawnLocation).Rotation();

	AICharacter->GetCharacterMovement()->StopMovementImmediately();

	FRotator LookAtRotation = (Player->GetActorLocation() - AICharacter->GetActorLocation()).Rotation();
	LookAtRotation.Pitch = 0.0f;
	AICharacter->SetActorRotation(LookAtRotation);

	UWorld* World = AICharacter->GetWorld();
	if (World)
	{
		AStone* SpawnedStone = World->SpawnActor<AStone>(AStone::StaticClass(), SpawnLocation, SpawnRotation);
		if (SpawnedStone)
		{
			FVector LaunchDirection = (Player->GetActorLocation() - SpawnLocation).GetSafeNormal();
			SpawnedStone->ProjectileMovement->Velocity = LaunchDirection * 1500.0f;

			SpawnedStone->SetOwnerInfo(AIController, AICharacter);
		}
	}

	AIController->GetBlackboardComponent()->SetValueAsBool("CanThrowAttack", false);

	FTimerHandle CoolDownTimer;
	AICharacter->GetWorldTimerManager().SetTimer(
		CoolDownTimer,
		FTimerDelegate::CreateLambda([AIController]()
			{
				if (AIController)
				{
					AIController->GetBlackboardComponent()->SetValueAsBool("CanThrowAttack", true);
				}
			}),
		10.0f,
		false
	);

	return EBTNodeResult::Succeeded;
}
