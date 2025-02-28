// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateAttackState.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UBTService_UpdateAttackState : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateAttackState();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
