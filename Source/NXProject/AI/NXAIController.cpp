// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXAIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

const float ANXAIController::PatrolRadius(1000.f);
int32 ANXAIController::ShowAIDebug(0);
const FName ANXAIController::StartPatrolPositionKey(TEXT("StartPatrolPosition"));
const FName ANXAIController::EndPatrolPositionKey(TEXT("EndPatrolPosition"));
const FName ANXAIController::TargetCharacterKey(TEXT("TargetCharacter"));

FAutoConsoleVariableRef CVarShowAIDebug2(
	TEXT("NXProject.ShowAIDebug"),
	ANXAIController::ShowAIDebug,
	TEXT(""),
	ECVF_Cheat
);

ANXAIController::ANXAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BrainComponent"));
}

void ANXAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* ControlledPawn = GetPawn();
	if (IsValid(ControlledPawn) == true)
	{
		BeginAI(ControlledPawn);
	}
}

void ANXAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EndAI();
	Super::EndPlay(EndPlayReason);
}

void ANXAIController::BeginAI(APawn* InPawn)
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
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("BegintAI()")));
			}
		}
	}
}

void ANXAIController::EndAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (IsValid(BehaviorTreeComponent) == true)
	{
		BehaviorTreeComponent->StopTree();
		if (ShowAIDebug == 1)
		{
			UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("EndAI()")));
		}
	}
}

