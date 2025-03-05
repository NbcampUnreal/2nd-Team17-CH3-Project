#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NXGameState.generated.h"

class APortalActor; // 전방 선언

UCLASS()
class NXPROJECT_API ANXGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ANXGameState();

    virtual void BeginPlay() override;

    // 점수를 가져오는 함수
    int32 GetScore() const;

    // 점수를 추가하는 함수
    void AddScore(int32 Amount);

    // 포탈 이펙트를 활성화하는 함수
    void ActivatePortalEffect();

    // PortalActor를 초기화하는 함수
    void InitializePortalActor(APortalActor* Portal);

    UFUNCTION(BlueprintCallable)
    void ShowWinGameUI();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> WinUserWidgetClass;


    //허드
    void UpdateHUD();

private:
    int32 Score; // 현재 점수
    int32 RequiredScoreToActivatePortal; // 포탈 활성화에 필요한 점수

    UPROPERTY()
    APortalActor* PortalActor; // 포탈 액터 참조
};