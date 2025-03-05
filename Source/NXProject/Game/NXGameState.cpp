#include "Game/NXGameState.h"
#include "Game/PortalActor.h"
#include "Engine/Engine.h"
#include "Player/NXPlayerController.h"
#include "Player/NXPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Game/NXGameInstance.h"
#include "Weapon/NXShotgun.h"

ANXGameState::ANXGameState()
{
	Score = 0;
	RequiredScoreToActivatePortal = 2; // 2킬 시 포탈 작동
	PortalActor = nullptr; // 초기화
}

void ANXGameState::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ANXGameState::UpdateHUD,
		0.1f,
		true
	);
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
void ANXGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ANXPlayerController* NXPlayerController = Cast<ANXPlayerController>(PlayerController);
		{
			if (UUserWidget* HUDWidget = NXPlayerController->GetHUDWidget())
			{
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"),Score,RequiredScoreToActivatePortal)));
				}

				if (UTextBlock* BulletText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Bullet"))))
				{
					ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(PlayerController->GetPawn());
					ANXShotgun* Shotgun = Cast<ANXShotgun>(PlayerCharacter->GetWeaponInstance());

					BulletText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Shotgun->GetBullet(),Shotgun->MaxBullet)));
				}
				if (UProgressBar* HPBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("PlayerHPBar"))))
				{
					ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(PlayerController->GetPawn());
					const float HPPercent = PlayerCharacter->GetHealth() / PlayerCharacter->MaxHealth;
					HPBar->SetPercent(HPPercent);
					if (HPPercent < 0.3f)
					{
						HPBar->SetFillColorAndOpacity(FLinearColor::Red);
					}
				}
			}
		}
	}
}