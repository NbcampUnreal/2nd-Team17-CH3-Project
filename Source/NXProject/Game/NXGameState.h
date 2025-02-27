#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NXGameState.generated.h"

UCLASS()
class NXPROJECT_API ANXGameState : public AGameState
{
	GENERATED_BODY()
	

public:
	ANXGameState();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Score")
	int32 Score;

	//virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore()const;
	UFUNCTION(BlueprintCallable,Category = "Score")
	void AddScore(int32 Amount);

};
