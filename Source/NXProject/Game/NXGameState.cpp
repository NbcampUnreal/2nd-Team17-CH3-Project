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
        PortalActor->ActivateEffect(); // 포탈 이펙트 활성화
    }
}

// PortalActor 초기화
void ANXGameState::InitializePortalActor(APortalActor* Portal)
{
    PortalActor = Portal;
}