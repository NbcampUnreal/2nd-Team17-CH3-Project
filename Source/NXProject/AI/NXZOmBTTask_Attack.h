#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NXZOmBTTask_Attack.generated.h"

UCLASS()
class NXPROJECT_API UNXZOmBTTask_Attack : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UNXZOmBTTask_Attack();

    /** ?? ?????? ????? ?¨ö?? (Tick) */
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    /** ???? ???? */
    void BeginAttack();

    /** ???? ???? */
    void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

    /** ???? ?????? ???? ??? */
    bool IsAttacking() const { return bIsNowAttacking; }

    /** ???? ?????? ???? */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    bool bIsNowAttacking;

private:
    /** ???? ?¨ö?? ???? */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
    void StartAttack() {
        BeginAttack();  // BeginAttack?? protected?? ??????, ??? ?????? public ????? ???
    }

};