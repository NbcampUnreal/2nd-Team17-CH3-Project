#include "Game/NXGameState.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"
#include "Player/NXPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Game/NXGameInstance.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToActivatePortal = 2; // 2ų �� ��Ż �۵�
    PortalActor = nullptr; // �ʱ�ȭ
}

void ANXGameState::BeginPlay()
{
    Super::BeginPlay();

  
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

    if (UGameInstance* GameInstance = GetGameInstance())
    {
        UNXGameInstance* NXGameInstance = Cast<UNXGameInstance>(GameInstance);
        if (NXGameInstance)
        {
            NXGameInstance->AddToScore(Amount);
        }
    }

    UpdateHUD();//���ھ� ���� �� ������Ʈ
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
/**
void ANXGameState::UpdateHUD()
{
    // �÷��̾� ��Ʈ�ѷ��� ��ȿ���� Ȯ��
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        // �÷��̾� ��Ʈ�ѷ��� NXPlayerController���� Ȯ��
        if (ANXPlayerController* NXPlayerController = Cast<ANXPlayerController>(PlayerController))
        {
            // HUD ������ ��ȿ���� Ȯ��
            if (UUserWidget* HUDWidget = NXPlayerController->GetHUDWidget())
            {
                // HUD �������� Score �ؽ�Ʈ ����� ã��
                if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
                {
                    // ���� �ν��Ͻ��� ��ȿ���� Ȯ��
                    if (UNXGameInstance* NXGameInstance = Cast<UNXGameInstance>(GetGameInstance()))
                    {
                        // TotalScore ���� ScoreText�� ������Ʈ
                        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NXGameInstance->TotalScore)));
                    }
                }
            }
        }
    }
}*/
void ANXGameState::UpdateHUD()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (ANXPlayerController* NXPlayerController = Cast<ANXPlayerController>(PlayerController))
        {
            if (UUserWidget* HUDWidget = NXPlayerController->GetHUDWidget())
            {
                if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
                {
                    if (UNXGameInstance* NXGameInstance = Cast<UNXGameInstance>(GetGameInstance()))
                    {
                        int32 CurrentScore = NXGameInstance->TotalScore;
                        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), CurrentScore)));

                        // ����� �α� �߰�
                        UE_LOG(LogTemp, Warning, TEXT("UpdateHUD: Score Updated to %d"), CurrentScore);
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("UpdateHUD: ScoreText not found!"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UpdateHUD: HUDWidget is nullptr!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UpdateHUD: PlayerController is not ANXPlayerController!"));
        }
    }
}