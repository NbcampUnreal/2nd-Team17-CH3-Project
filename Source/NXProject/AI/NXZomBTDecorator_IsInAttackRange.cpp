#include "AI/NXZomBTDecorator_IsInAttackRange.h"
#include "AI/NXZombieAIController.h"
#include "AI/NXZombieCharacter.h"
#include "Player/NXCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UNXZomBTDecorator_IsInAttackRange::AttackRange(200.f);

UNXZomBTDecorator_IsInAttackRange::UNXZomBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("ISInAttackRange");
}

bool UNXZomBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	checkf(bResult == true, TEXT("Super::CalculateRawConditionValue() function has returned false."));

	ANXZombieAIController* AIController = Cast<ANXZombieAIController>(OwnerComp.GetAIOwner());
	checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

	ANXZombieCharacter* NPC = Cast<ANXZombieCharacter>(AIController->GetPawn());
	checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

	ANXCharacterBase* TargetPlayerCharacter = Cast<ANXCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANXZombieAIController::TargetCharacterKey));
	if (IsValid(TargetPlayerCharacter) == true && TargetPlayerCharacter->IsPlayerControlled() == true)
	{
		return NPC->GetDistanceTo(TargetPlayerCharacter) <= AttackRange;
	}

	return false;
}
