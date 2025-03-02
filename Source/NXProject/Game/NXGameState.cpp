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

    // ������ ȭ�鿡 ǥ��
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));

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
        UE_LOG(LogTemp, Log, TEXT("��Ż"));
        PortalActor->ActivateEffect(); // ��Ż ����Ʈ Ȱ��ȭ
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PortalActor�� �ʱ�ȭ���� �ʾҽ��ϴ�!"));
    }
}

// PortalActor �ʱ�ȭ
void ANXGameState::InitializePortalActor(APortalActor* Portal)
{
    PortalActor = Portal;
    UE_LOG(LogTemp, Log, TEXT("PortalActor�� �ʱ�ȭ�Ǿ����ϴ�."));
}