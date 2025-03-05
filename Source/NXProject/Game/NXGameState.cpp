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
	RequiredScoreToActivatePortal = 2; // 2ų �� ��Ż �۵�
	PortalActor = nullptr; // �ʱ�ȭ
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