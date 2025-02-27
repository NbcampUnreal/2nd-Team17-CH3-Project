//#include "AI/NXZomBTTask_TurnToTarget.h"
//#include "AI/NXZombieAIController.h"
//#include "AI/NXZombieCharacter.h"
//#include "Player/NXCharacterBase.h"
//#include "Player/NXPlayerCharacter.h"
//#include "BehaviorTree/BlackboardComponent.h"
//
//
//UNXZomBTTask_TurnToTarget::UNXZomBTTask_TurnToTarget()
//{
//    NodeName = TEXT("TurnToTargetActor");
//}
//
//EBTNodeResult::Type UNXZomBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
//
//    ANXZombieAIController* AIController = Cast<ANXZombieAIController>(OwnerComp.GetAIOwner());
//    checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));
//
//    ANXZombieCharacter* NPC = Cast<ANXZombieCharacter>(AIController->GetPawn());
//    checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));
//
//    if (ANXCharacterBase* TargetPC = Cast<ANXCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->TargetCharacterKey)))
//    {
//        FVector LookVector = TargetPC->GetActorLocation() - NPC->GetActorLocation();
//        LookVector.Z = 0.f;
//        FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
//        NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.f));
//
//        return Result = EBTNodeResult::Succeeded;
//    }
//
//    return Result = EBTNodeResult::Failed;
//}