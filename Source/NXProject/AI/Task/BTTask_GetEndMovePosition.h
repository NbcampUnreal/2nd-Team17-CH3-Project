// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetEndMovePosition.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UBTTask_GetEndMovePosition : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetEndMovePosition();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
