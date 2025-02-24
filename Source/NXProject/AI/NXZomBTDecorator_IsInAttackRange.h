#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "NXZomBTDecorator_IsInAttackRange.generated.h"


UCLASS()
class NXPROJECT_API UNXZomBTDecorator_IsInAttackRange : public UBTDecorator
{
    GENERATED_BODY()

public:
    UNXZomBTDecorator_IsInAttackRange();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
    static const float AttackRange;


};