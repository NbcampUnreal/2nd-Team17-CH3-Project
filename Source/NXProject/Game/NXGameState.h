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
	int32 Score;// 전역 점수 저장

	//virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore()const;//현재 점수 읽기

	UFUNCTION(BlueprintCallable,Category = "Score")
	void AddScore(int32 Amount);// 점수 추가

	void SpawnPortal();//포탈 스폰


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	TSubclassOf<class APortalActor> PortalClass; // 스폰할 포탈 액터 클래스 //블프가능


private:
	int32 RequiredScoreToSpawnPortal; // 포탈 생성에 필요한 킬 카운트


	UPROPERTY(EditDefaultsOnly, Category = "Portal")
	FVector PortalSpawnLocation; // 포탈 스폰 위치

};
