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

//	void OnZombieKilled(); //좀비 처치 시 호출될 함수
//
//	void SpawnPortal(); //포탈 스폰 함수
//
//protected:
//	virtual void BeginPlay() override;
//
//private:
//
//	int32 ZombiesKilled; //현재 킬 카운트

UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Score")
	int32 Score;

	//virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore()const;
	UFUNCTION(BlueprintCallable,Category = "Score")
	void AddScore(int32 Amount);

};
