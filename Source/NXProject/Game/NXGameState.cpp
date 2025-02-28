#include "Game/NXGameState.h"
#include "Player/NXPlayerController.h"
#include "Components/TextBlock.h"
#include "Game/NXGameInstance.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"


ANXGameState::ANXGameState()
{
	Score = 0;
	//RequiredScoreToSpawnPortal = 10; //10���� óġ �� ��Ż ����
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
//	if (Score >= 10) //10ų �̻��� ��
//	{
//		if (PortalClass)
//		{
//			Fvector PotalSpawnLocation = FVector(0.f); //��ȣ �ȿ� ��Ż ��ġ ����
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