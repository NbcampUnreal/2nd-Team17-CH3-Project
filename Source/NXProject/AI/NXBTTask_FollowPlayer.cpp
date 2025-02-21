// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXBTTask_FollowPlayer.h"
#include "AI/NXAIController.h"
#include "AI/NXNonPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

UNXBTTask_FollowPlayer::UNXBTTask_FollowPlayer()
{
    NodeName = TEXT("FollowPlayer");
}

EBTNodeResult::Type UNXBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) 
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) 
    {
        return EBTNodeResult::Failed;
    }

    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!TargetActor) 
    {
        return EBTNodeResult::Failed;
    }
    ANXNonPlayerCharacter* NPC = Cast< ANXNonPlayerCharacter>(AIController->GetPawn());
    if (NPC)
    {
        NPC->GetCharacterMovement()->MaxWalkSpeed = NPC->RunSpeed;
    }
    // 대상 위치로 이동
    AIController->MoveToActor(TargetActor, 100.0f);

    return EBTNodeResult::Succeeded;
}