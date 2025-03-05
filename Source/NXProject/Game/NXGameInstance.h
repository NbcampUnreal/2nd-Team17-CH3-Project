#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Game/NXGameState.h"
#include "NXGameInstance.generated.h"


UCLASS()
class NXPROJECT_API UNXGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNXGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddToScore(int32 Amount);

	// 스코어를 업데이트하는 함수
	void UpdateScore(int32 ScoreDelta);
};
