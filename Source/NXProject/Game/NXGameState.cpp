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

////코인스폰대신 좀비로 킬드좀비카운트=0 // 
////한 웨이브에서 스폰할 좀비 개수 
////스폰볼륨을 이용해서 좀비 스폰




