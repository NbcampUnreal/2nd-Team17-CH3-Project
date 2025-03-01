
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NXBTTask_BackJump.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UNXBTTask_BackJump : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UNXBTTask_BackJump();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
