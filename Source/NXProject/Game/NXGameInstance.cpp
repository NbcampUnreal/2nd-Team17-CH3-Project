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
    // ���� ������Ʈ �� HUD�� �ٽ� ������Ʈ�ϵ��� ȣ��
    if (ANXGameState* GameState = GetWorld()->GetGameState<ANXGameState>())
    {
        GameState->UpdateHUD();  // ������ ����� �� HUD ������Ʈ
    }
}
