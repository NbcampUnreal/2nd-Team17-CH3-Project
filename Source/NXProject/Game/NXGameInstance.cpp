#include "Game/NXGameInstance.h"

UNXGameInstance::UNXGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UNXGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}