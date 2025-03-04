#include "Game/NXGameState.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToActivatePortal = 2; // 2ų �� ��Ż �۵�
    PortalActor = nullptr; // �ʱ�ȭ
}

int32 ANXGameState::GetScore() const
{
    return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
    Score += Amount;

    // ��Ż ����Ʈ Ȱ��ȭ ���� Ȯ��
    if (Score >= RequiredScoreToActivatePortal && PortalActor)
    {
        ActivatePortalEffect(); // ��Ż ����Ʈ ��� Ȱ��ȭ
    }
}

void ANXGameState::ActivatePortalEffect()
{
    if (PortalActor)
    {
        PortalActor->ActivateEffect(); // ��Ż ����Ʈ Ȱ��ȭ
    }
}

// PortalActor �ʱ�ȭ
void ANXGameState::InitializePortalActor(APortalActor* Portal)
{
    PortalActor = Portal;
}