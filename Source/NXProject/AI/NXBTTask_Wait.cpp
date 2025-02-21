// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXBTTask_Wait.h"
#include "BehaviorTree/BlackboardComponent.h"

UNXBTTask_Wait::UNXBTTask_Wait()
{
	NodeName = TEXT("Wait");
}

EBTNodeResult::Type UNXBTTask_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CurrentOwnerComp = &OwnerComp;
	float WaitTime = FMath::RandRange(0.5f, 2.0f);

	GetWorld()->GetTimerManager().SetTimer(
		WaitTimerHandle,
		this,
		&UNXBTTask_Wait::OnWaitTimeFinished,
		WaitTime,
		false
	);

	return EBTNodeResult::InProgress;
}


void UNXBTTask_Wait::OnWaitTimeFinished()
{
	FinishLatentTask(*CurrentOwnerComp, EBTNodeResult::Succeeded);
}