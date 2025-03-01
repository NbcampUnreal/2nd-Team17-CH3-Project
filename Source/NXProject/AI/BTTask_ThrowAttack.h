// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ThrowAttack.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UBTTask_ThrowAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ThrowAttack();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
