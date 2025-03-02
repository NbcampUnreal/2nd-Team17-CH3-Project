#include "Game/NXGameState.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToActivatePortal = 2; // 2킬 시 포탈 작동
    PortalActor = nullptr; // 초기화
}

int32 ANXGameState::GetScore() const
{
    return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
    Score += Amount;

    // 점수를 화면에 표시
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));

    // 포탈 이펙트 활성화 조건 확인
    if (Score >= RequiredScoreToActivatePortal && PortalActor)
    {
        ActivatePortalEffect(); // 포탈 이펙트 즉시 활성화
    }
}

void ANXGameState::ActivatePortalEffect()
{
    if (PortalActor)
    {
        UE_LOG(LogTemp, Log, TEXT("포탈"));
        PortalActor->ActivateEffect(); // 포탈 이펙트 활성화
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PortalActor가 초기화되지 않았습니다!"));
    }
}

// PortalActor 초기화
void ANXGameState::InitializePortalActor(APortalActor* Portal)
{
    PortalActor = Portal;
    UE_LOG(LogTemp, Log, TEXT("PortalActor가 초기화되었습니다."));
}