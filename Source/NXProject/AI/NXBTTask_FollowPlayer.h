
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NXBTTask_FollowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UNXBTTask_FollowPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UNXBTTask_FollowPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;
};
