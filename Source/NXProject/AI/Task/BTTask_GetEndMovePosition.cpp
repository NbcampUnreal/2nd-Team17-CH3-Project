// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_GetEndMovePosition.h"
#include "AI/NXAIController.h"
#include "AI/NXNonPlayerCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetEndMovePosition::UBTTask_GetEndMovePosition()
{
	NodeName = TEXT("GetEndMovePosition");
}

EBTNodeResult::Type UBTTask_GetEndMovePosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (EBTNodeResult::Failed == Result)
	{
		return Result;
	}

	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	checkf(IsValid(AIController) == true, TEXT("Invalid AIController"));

	ANXNonPlayerCharacter* NPC = Cast<ANXNonPlayerCharacter>(AIController->GetPawn());
	checkf(IsValid(NPC) == true, TEXT("Invalid NPC"));

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(NPC->GetWorld());
	checkf(IsValid(NavigationSystem) == true, TEXT("Invalid NavigationSystem"));

	FVector StartPatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ANXAIController::StartPatrolPositionKey);
	FNavLocation EndPatrolLocation;
	if (true == NavigationSystem->GetRandomPointInNavigableRadius(StartPatrolPosition, AIController->PatrolRadius, EndPatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ANXAIController::EndPatrolPositionKey, EndPatrolLocation.Location);
		return Result = EBTNodeResult::Succeeded;
	}
	return Result;
}
