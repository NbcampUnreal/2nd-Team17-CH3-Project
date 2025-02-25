#include "AI/NXZOmBTTask_Attack.h"
#include "AI/NXZombieCharacter.h"
#include "AI/NXZombieAIController.h"



UNXZOmBTTask_Attack::UNXZOmBTTask_Attack()
{
    bNotifyTick = true;
}

void UNXZOmBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ANXZombieAIController* AIController = Cast<ANXZombieAIController>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

    ANXZombieCharacter* NPC = Cast<ANXZombieCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

    if (!NPC->IsNowAttacking())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

EBTNodeResult::Type UNXZOmBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ANXZombieAIController* AIController = Cast<ANXZombieAIController>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController), TEXT("Invalid AIController."));

    ANXZombieCharacter* NPC = Cast<ANXZombieCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC), TEXT("Invalid NPC."));

    // ???? ????
    NPC->StartAttack(); // StartAttack?? ?????? BeginAttack?? ????

    return EBTNodeResult::InProgress;
}

// UNXZOmBTTask_Attack.cpp
void UNXZOmBTTask_Attack::BeginAttack()
{
    // ???? ????
}