#include "Game/NXGameInstance.h"

UNXGameInstance::UNXGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UNXGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
}

void UNXGameInstance::UpdateScore(int32 ScoreDelta)
{
    TotalScore += ScoreDelta;
    // 총점 업데이트 후 HUD를 다시 업데이트하도록 호출
    if (ANXGameState* GameState = GetWorld()->GetGameState<ANXGameState>())
    {
        GameState->UpdateHUD();  // 총점이 변경된 후 HUD 업데이트
    }
}
