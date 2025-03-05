#include "Game/NXGameState.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"
#include "Player/NXPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UI/WInUserWidget.h"
#include "Game/NXGameInstance.h"

ANXGameState::ANXGameState()
{
    Score = 0;
    RequiredScoreToActivatePortal = 2; // 2킬 시 포탈 작동
    PortalActor = nullptr; // 초기화
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

    // 포탈 이펙트 활성화 조건 확인
    if (Score >= RequiredScoreToActivatePortal && PortalActor)
    {
        ActivatePortalEffect(); // 포탈 이펙트 즉시 활성화
    }

    if (UGameInstance* GameInstance = GetGameInstance())
    {
        UNXGameInstance* NXGameInstance = Cast<UNXGameInstance>(GameInstance);
        if (NXGameInstance)
        {
            NXGameInstance->AddToScore(Amount);
        }
    }

    UpdateHUD();//스코어 변경 시 업데이트
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

void ANXGameState::ShowWinGameUI()
{
    if (WinUserWidgetClass) 
    {
        UWInUserWidget* WinUserWidget = CreateWidget<UWInUserWidget>(GetWorld(), WinUserWidgetClass);
        if (WinUserWidget)
        {
            WinUserWidget->AddToViewport(); 

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(WinUserWidget->TakeWidget());
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;
            }
        }
    }
}

void ANXGameState::UpdateHUD()
{
    // 플레이어 컨트롤러가 유효한지 확인
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        // 플레이어 컨트롤러가 NXPlayerController인지 확인
        if (ANXPlayerController* NXPlayerController = Cast<ANXPlayerController>(PlayerController))
        {
            // HUD 위젯이 유효한지 확인
            if (UUserWidget* HUDWidget = NXPlayerController->GetHUDWidget())
            {
                // HUD 위젯에서 Score 텍스트 블록을 찾음
                if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
                {
                    if (UGameInstance* GameInstance = GetGameInstance())
                    {
                        // 게임 인스턴스가 유효한지 확인
                        if (UNXGameInstance* NXGameInstance = Cast<UNXGameInstance>(GetGameInstance()))
                        {
                            // TotalScore 값을 ScoreText에 업데이트
                            ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NXGameInstance->TotalScore)));
                        }
                    }
                    
                }
            }
        }
    }
}