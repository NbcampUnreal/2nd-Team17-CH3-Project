// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXBTTask_Wait.h"

UNXBTTask_Wait::UNXBTTask_Wait()
{
	NodeName = TEXT("Wait");
}

EBTNodeResult::Type UNXBTTask_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float WaitTime = FMath::RandRange(0.5f, 2.0f);



	return EBTNodeResult::Type();
}
