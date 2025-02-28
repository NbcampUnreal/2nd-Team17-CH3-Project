#include "Game/NXGameState.h"
#include "Player/NXPlayerController.h"
#include "Components/TextBlock.h"
#include "Game/NXGameInstance.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToSpawnPortal = 10; // 10���� óġ �� ��Ż ����
}

int32 ANXGameState::GetScore() const
{
    return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
    Score += Amount;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));

    if (Score >= RequiredScoreToSpawnPortal) // 10ų �̻��� ��
    {
        if (PortalClass)
        {
            FVector SpawnLocation = FVector(0.f, 0.f, 100.f); // ��Ż ��ġ ����
            FRotator PortalRotation = FRotator::ZeroRotator;

            GetWorld()->SpawnActor<AActor>(PortalClass, SpawnLocation, PortalRotation);
            UE_LOG(LogTemp, Log, TEXT("��Ż�� �����Ǿ����ϴ�!�ǝo ����� ���Y!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("PortalClass�� �������� �ʾҽ��ϴ�!"));
        }
    }
}
