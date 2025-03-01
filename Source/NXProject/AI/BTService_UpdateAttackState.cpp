
#include "AI/BTService_UpdateAttackState.h"
#include "AI/NXAIController.h"
#include "AI/NXBossZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_UpdateAttackState::UBTService_UpdateAttackState()
{
	NodeName = "UpdateAttackState";
	Interval = 0.5f;
}

void UBTService_UpdateAttackState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ANXAIController* AIController = Cast<ANXAIController>(OwnerComp.GetAIOwner());
    if (!AIController) return;

    ANXBossZombie* AICharacter = Cast<ANXBossZombie>(AIController->GetPawn());
    if (!AICharacter) return;

    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Player) return;

    UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
    if (!BlackboardComp)return;

    float Distance = FVector::Dist(Player->GetActorLocation(), AICharacter->GetActorLocation());
    BlackboardComp->SetValueAsFloat("PlayerDistance", Distance);

    bool bCanJumpAttack = BlackboardComp->GetValueAsBool("CanJumpAttack");
    bool bCanDashAttack = BlackboardComp->GetValueAsBool("CanDashAttack");
    bool bCanMeleeAttack = BlackboardComp->GetValueAsBool("CanMeleeAttack");
    bool bCanThrowAttack = BlackboardComp->GetValueAsBool("CanThrowAttack");

    bool bInMeleeRange = BlackboardComp->GetValueAsBool("InMeleeRange");
    bool bInMiddleRange = BlackboardComp->GetValueAsBool("InMiddleRange");
    bool bInLongRange = BlackboardComp->GetValueAsBool("InLongRange");

    if (Distance >= 1200.0f && Distance <= 1500.0f)
    {
        bInLongRange = true;
    }
    else
    {
        bInLongRange = false;
    }

    if (Distance >= 500.0f && Distance <= 1000.0f)
    {
        bInMiddleRange = true;
    }
    else
    {
        bInMiddleRange = false;
    }

    if (Distance <= 150.0f && bCanMeleeAttack)
    {
        bInMeleeRange = true;
    }
    else
    {
        bInMeleeRange = false;
    }

    if (bInLongRange && bCanJumpAttack)
    {
        BlackboardComp->SetValueAsBool("DoJumpAttack", true);
        BlackboardComp->SetValueAsBool("DoThrowAttack", true);
    }
    else
    {
        BlackboardComp->SetValueAsBool("DoJumpAttack", false);
        BlackboardComp->SetValueAsBool("DoThrowAttack", false);
    }

    if (bInMiddleRange && bCanDashAttack)
    {
        BlackboardComp->SetValueAsBool("DoDashAttack", true);
    }
    else
    {
        BlackboardComp->SetValueAsBool("DoDashAttack", false);
    }

    if (bInMeleeRange)
    {
        BlackboardComp->SetValueAsBool("DoMeleeAttack", true);
    }
    else
    {
        BlackboardComp->SetValueAsBool("DoMeleeAttack", false);
    }
}