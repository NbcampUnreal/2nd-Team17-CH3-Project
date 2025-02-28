#include "Game/NXGameState.h"
#include "Player/NXPlayerController.h"
#include "Components/TextBlock.h"
#include "Game/NXGameInstance.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"


ANXGameState::ANXGameState()
{
	Score = 0;
	//RequiredScoreToSpawnPortal = 10; //10마리 처치 시 포탈 생성
}

int32 ANXGameState::GetScore() const
{
	return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
	Score += Amount;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));
//
//	if (Score >= 10) //10킬 이상일 때
//	{
//		if (PortalClass)
//		{
//			Fvector PotalSpawnLocation = FVector(0.f); //괄호 안에 포탈 위치 적기
//			F
//		}
//	}
}



/*
void ANXGameState::SpawnPortal()
{
	if (PortalClass)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<APortalActor>(PortalClass, PortalSpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}
*/