// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NXBTTask_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UNXBTTask_RandomMove : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UNXBTTask_RandomMove();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
