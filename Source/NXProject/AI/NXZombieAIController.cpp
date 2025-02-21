#include "AI/NXZombieAIController.h"
#include "AI/NXZombieCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// 패트롤 간격과 패트롤 반경 설정
// const float ANXZombieAIController::PatrolRepeatInterval(3.f);
const float ANXZombieAIController::PatrolRadius(500.f);
int32 ANXZombieAIController::ShowAIDebug(0);
const FName ANXZombieAIController::StartPatrolPositionKey(TEXT("StartPatrolPosition"));
const FName ANXZombieAIController::EndPatrolPositionKey(TEXT("EndPatrolPosition"));
const FName ANXZombieAIController::TargetCharacterKey(TEXT("TargetCharacter"));



FAutoConsoleVariableRef CVarShowAIDebug(
	TEXT("NXProject.ShowAIDebug"),
	ANXZombieAIController::ShowAIDebug,
	TEXT(""),
	ECVF_Cheat
);

ANXZombieAIController::ANXZombieAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BrainComponent"));

}

void ANXZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	// 일정 시간마다 패트롤 실행
	//GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, this, &ThisClass::OnPatrolTimerElapsed, PatrolRepeatInterval, true);

	APawn* ControlledPawn = GetPawn();
	if (IsValid(ControlledPawn) == true)
	{
		BeginAI(ControlledPawn);
	}
}


void ANXZombieAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);
	EndAI();

	Super::EndPlay(EndPlayReason);
}

void ANXZombieAIController::BeginAI(APawn* InPawn)
{
	UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Blackboard);
	if (IsValid(BlackboardComponent) == true)
	{
		if (UseBlackboard(BlackboardDataAsset, BlackboardComponent) == true)
		{
			bool bRunSucceeded = RunBehaviorTree(BehaviorTree);
			checkf(bRunSucceeded == true, TEXT("Fail to run behavior tree."));
			BlackboardComponent->SetValueAsVector(StartPatrolPositionKey, InPawn->GetActorLocation());

			if (ShowAIDebug == 1)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("BeginAI() has been called.")));
			}
		}
	}
}

void ANXZombieAIController::EndAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (IsValid(BehaviorTreeComponent) == true)
	{
		BehaviorTreeComponent->StopTree();

		if (ShowAIDebug == 1)
		{
			UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("EndAI() has been called.")));
		}
	}
}


/*
void ANXZombieAIController::OnPatrolTimerElapsed()
{
	// AI가 조종하는 Pawn 가져오기
	APawn* ControlledPawn = GetPawn();
	if (IsValid(ControlledPawn) == true)
	{
		// 네비게이션 시스템 가져오기
		UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (IsValid(NavigationSystem) == true)
		{
			FVector ActorLocation = ControlledPawn->GetActorLocation();
			FNavLocation NextLocation;

			// 이동 가능한 랜덤 위치 찾기
			if (NavigationSystem->GetRandomPointInNavigableRadius(ActorLocation, PatrolRadius, NextLocation) == true)
			{

				// 해당 위치로 이동
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
			}
		}
	}
}
*/
