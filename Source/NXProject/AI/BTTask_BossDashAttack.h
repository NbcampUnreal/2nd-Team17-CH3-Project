// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossDashAttack.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UBTTask_BossDashAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossDashAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
