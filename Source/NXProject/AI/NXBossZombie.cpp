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
				DrawDebugSphere(GetWorld(), AttackLocation, JumpAttackRadius, 16, FColor::Green, false, 2.f);
			}
		}
	}
	else
	{
		DrawDebugSphere(GetWorld(), AttackLocation, JumpAttackRadius, 16, FColor::Red, false, 2.f);
	}

	bIsJumpAttacking = false;
	GetCharacterMovement()->GravityScale = 1.0f;
}