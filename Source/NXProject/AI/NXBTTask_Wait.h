// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NXBTTask_Wait.generated.h"

/**
 *
 */
UCLASS()
class NXPROJECT_API UNXBTTask_Wait : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNXBTTask_Wait();

	UBehaviorTreeComponent* CurrentOwnerComp = nullptr;
	FTimerHandle WaitTimerHandle;

	void OnWaitTimeFinished();


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
