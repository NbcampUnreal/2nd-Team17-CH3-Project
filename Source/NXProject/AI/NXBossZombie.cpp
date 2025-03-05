// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXBossZombie.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NXPlayerCharacter.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXBossZombie::ANXBossZombie()
{
	MaxHealth = 300.0f;
	Health = MaxHealth;

	// WinScreenClass �⺻�� ����
	static ConstructorHelpers::FClassFinder<UUserWidget> WinScreenClassFinder(TEXT("/Blueprint/UI/WBP_WinScreen"));
	if (WinScreenClassFinder.Class)
	{
		WinScreenClass = WinScreenClassFinder.Class;
	}

}

void ANXBossZombie::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (!bIsJumpAttacking)return;

	FVector AttackLocation = GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(NAME_None, false, this);

	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		AttackLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(JumpAttackRadius),
		CollisionQueryParams
	);
	if (bResult == true)
	{
		AController* OwnerController = GetController();
		TSet<AActor*> HitPlayers;

		for (auto const& OverlapResult : OverlapResults)
		{
			ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(OverlapResult.GetActor());
			if (IsValid(PlayerCharacter) && !HitPlayers.Contains(PlayerCharacter))
			{
				PlayerCharacter->TakeDamage(JumpAttackDamage, FDamageEvent(), OwnerController, this);
				HitPlayers.Add(PlayerCharacter);
			}
		}
	}

	bIsJumpAttacking = false;
	GetCharacterMovement()->GravityScale = 1.0f;
}

void ANXBossZombie::DashAttack()
{
	GetWorldTimerManager().SetTimer(
		DashHitTimer,
		this,
		&ANXBossZombie::OnDashHit,
		0.2f,
		true
	);

	GetWorldTimerManager().SetTimer(
		DashEndTimer,
		this,
		&ANXBossZombie::StopDash,
		0.6f,
		false
	);
}


void ANXBossZombie::StopDash()
{
	bIsDashAttacking = false;

	GetWorldTimerManager().ClearTimer(DashHitTimer);
}

void ANXBossZombie::OnDashHit()
{
	if (!GetWorld()) return;

	FVector Center = GetActorLocation();
	float Radius = 200.0f;
	AController* OwnerController = GetController();

	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Center,
		Center,
		FQuat::Identity,
		ECC_Pawn,
		CollisionShape,
		QueryParams
	);

	if (bHit)
	{
		for (FHitResult Hit : HitResults)
		{
			ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(Hit.GetActor());
			if (PlayerCharacter)
			{
				PlayerCharacter->TakeDamage(DashAttackDamage, FDamageEvent(), OwnerController, this);
			}
		}
	}

}

void ANXBossZombie::OnDeath()
{
	Super::OnDeath();
	// ������ �׾��� �� ȣ��Ǵ� �Լ�
	if (WinScreenClass)
	{
		// WinScreen UI ����
		UUserWidget* WinScreen = CreateWidget<UUserWidget>(GetWorld(), WinScreenClass);
		if (WinScreen)
		{
			// UI�� ȭ�鿡 �߰�
			WinScreen->AddToViewport();

			// �÷��̾� �Է� ��Ȱ��ȭ
			APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC)
			{
				PC->SetInputMode(FInputModeUIOnly()); // UI�� �Է� ����
				PC->bShowMouseCursor = true; // ���콺 Ŀ�� ǥ��
			}
		}
	}
}
