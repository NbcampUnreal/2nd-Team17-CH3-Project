#include "Game/NXGameState.h"
#include "Player/NXPlayerController.h"
#include "Components/TextBlock.h"
#include "Game/NXGameInstance.h"
#include "Engine/Engine.h"


ANXGameState::ANXGameState()
{
	Score = 0;

	/*Score = 0;
	CurrentWaveIndex = 0;
	MaxWaves = 2;
	ZombiesToSpawnPerWave = { 30, 50 };
	KilledZombieCount = 0;*/
}

//void ANXGameState::BeginPlay()
//{
//	Super::BeginPlay();
//
//	GetWorldTimeManger().SetTimer(
//		HUDUpdateTimerHandle,
//		this,
//		&ANXGameState::UpdateHUD,
//		0.1f,
//		true
//	);
//}

int32 ANXGameState::GetScore() const
{
	return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
	Score += Amount;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));
}

////���ν������ ����� ų������ī��Ʈ=0 // 
////�� ���̺꿡�� ������ ���� ���� 
////���������� �̿��ؼ� ���� ����




