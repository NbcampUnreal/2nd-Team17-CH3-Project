// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXBossZombie.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NXPlayerCharacter.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"

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
				DrawDebugSphere(GetWorld(), AttackLocation, 30.f, 16, FColor::Green, false, 5.f);
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Hit Player!"));
				}
			}
		}
	}
	else
	{
		DrawDebugSphere(GetWorld(), AttackLocation, 30.f, 16, FColor::Red, false, 5.f);
	}

	bIsJumpAttacking = false;
}