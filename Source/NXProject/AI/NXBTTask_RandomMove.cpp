
#include "AI/NXBTTask_RandomMove.h"
#include "AI/NXAIController.h"
#include "AI/NXNonPlayerCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UNXBTTask_RandomMove::UNXBTTask_RandomMove()
{
	NodeName = TEXT("RandomMove");
}

EBTNodeResult::Type UNXBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn())
    {
        ANXNonPlayerCharacter* NPC = Cast<ANXNonPlayerCharacter>(ControlledPawn);
        NPC->GetCharacterMovement()->MaxWalkSpeed = NPC->WalkSpeed;
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(ControlledPawn);

        if (NavSystem)
        {
            FNavLocation RandomLocation;
            float MoveRadius = 300.0f; //랜덤 범위
            float MinMoveDistance = 100.0f;//최소 이동 범위

            bool bFoundValidLocation = false;

            for (int i = 0; i < 10;i++)
            {
                if (NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), MoveRadius, RandomLocation))
                {
                    float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), RandomLocation.Location);

                    if (Distance >= MinMoveDistance)
                    {
                        bFoundValidLocation = true;
                        break;
                    }
                }
            }
            if (bFoundValidLocation)
            {
                OwnerComp.GetAIOwner()->MoveToLocation(RandomLocation.Location);

                return EBTNodeResult::Succeeded;
            }

        }

    }

    return EBTNodeResult::Failed;
}
