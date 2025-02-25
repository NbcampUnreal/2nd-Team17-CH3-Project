// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MoveToTarget.h"
#include "AI/NXAIController.h"
#include "AI/NXNonPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("MoveToTarget");
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (EBTNodeResult::Failed == Result)
	{
		return Result;
	}
	ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
	ANXNonPlayerCharacter* NPC = Cast<ANXNonPlayerCharacter>(AIController->GetPawn());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	FVector TargetLocation = BlackboardComp->GetValueAsVector("TargetLocation");

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
	if (TargetActor)
	{
		TargetLocation = TargetActor->GetActorLocation();
	}

	bool bIsChasing = BlackboardComp->GetValueAsBool("IsChasing");
	NPC->GetCharacterMovement()->MaxWalkSpeed = bIsChasing ? RunSpeed : WalkSpeed;

	AIController->MoveToLocation(TargetLocation);


	return EBTNodeResult::Succeeded;
}
