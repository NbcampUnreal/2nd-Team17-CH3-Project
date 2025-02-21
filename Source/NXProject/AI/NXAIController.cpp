// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXAIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystemTypes.h"
#include "Navigation/PathFollowingComponent.h"

void ANXAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ANXAIController::BeginPlay()
{
	Super::BeginPlay();
    RandomMove();
}

void ANXAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    if (Result.IsSuccess())
    {
        StopMoveTime = FMath::RandRange(0.5f, 2.0f);
        GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ANXAIController::RandomMove, StopMoveTime, false);
    }
    else
    {
        RandomMove();
    }
}

void ANXAIController::RandomMove()
{
    if (APawn* ControlledPawn = GetPawn())
    {
        UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

        if (NavSystem)
        {
            FNavLocation RandomLocation;
            float MoveRadius = 300.0f; //랜덤 범위
            float MinMoveDistance = 100.0f;//최소 이동 범위

            bool bFoundValidLocation = false;

            for (int i = 0; i < 10;i++)
            {
                if (NavSystem->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), MoveRadius, RandomLocation))
                {
                    float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), RandomLocation.Location);

                    if (Distance >= MinMoveDistance)
                    {
                        bFoundValidLocation = true;
                        break;
                    }
                }
            }

            if (bFoundValidLocation)
            {
                MoveToLocation(RandomLocation.Location);
            }
            else
            {
                GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ANXAIController::RandomMove, StopMoveTime, false);
            }
        }
    }
}

void ANXAIController::StopMove()
{
    GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
    StopMovement();
}

void ANXAIController::FollowPlayer(APawn* Player)
{
    //블랙보드로 구현 후 다시 구현
   /* if (!Player) return;

    StopMovement();

    GetWorld()->GetTimerManager().SetTimer(
        MoveTimerHandle,
        [this, Player]() 
        {
            if (Player && GetPawn())
            {
                MoveToActor(Player, 100.0f);
            }
        },
        1.0f,
        false
    );*/
}

