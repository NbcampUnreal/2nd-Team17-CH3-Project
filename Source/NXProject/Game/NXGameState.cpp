#include "Game/NXGameState.h"
#include "Player/NXPlayerController.h"
#include "Components/TextBlock.h"
#include "Game/NXGameInstance.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToSpawnPortal = 10; // 10마리 처치 시 포탈 생성
}

int32 ANXGameState::GetScore() const
{
    return Score;
}

void ANXGameState::AddScore(int32 Amount)
{
    Score += Amount;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Score: %d"), Score));

    if (Score >= RequiredScoreToSpawnPortal) // 10킬 이상일 때
    {
        if (PortalClass)
        {
            FVector SpawnLocation = FVector(0.f, 0.f, 100.f); // 포탈 위치 설정
            FRotator PortalRotation = FRotator::ZeroRotator;

            GetWorld()->SpawnActor<AActor>(PortalClass, SpawnLocation, PortalRotation);
            UE_LOG(LogTemp, Log, TEXT("포탈이 생성되었습니다!뽀쓔 무찌르러 가쟛!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("PortalClass가 설정되지 않았습니다!"));
        }
    }
}
