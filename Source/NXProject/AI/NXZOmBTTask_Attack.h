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

	/** 매 프레임 호출되는 태스크 (Tick) */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** 공격 시작 */
	void BeginAttack();

	/** 공격 종료 */
	void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

	/** 공격 중인지 여부 확인 */
	bool IsAttacking() const { return bIsNowAttacking; }

	/** 공격 중인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsNowAttacking;

private:
	/** 공격 태스크 실행 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	void StartAttack() {
		BeginAttack();  // BeginAttack은 protected로 남겨두고, 이를 호출하는 public 메서드 추가
	}

};
