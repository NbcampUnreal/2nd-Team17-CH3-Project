// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animation/NXNPCAnimInstance.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Player/NXPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

void UNXNPCAnimInstance::AnimNotify_CheckHit()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)return;

	FVector AttackLocation = PawnOwner->GetActorLocation() + PawnOwner->GetActorForwardVector() * 100.f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(NAME_None, false, PawnOwner);

	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		AttackLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(30.f),
		CollisionQueryParams
	);

	if (bResult == true)
	{
		AController* OwnerController = PawnOwner->GetController();
		TSet<AActor*> HitPlayers;

		for (auto const& OverlapResult : OverlapResults)
		{
			ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(OverlapResult.GetActor());
			if (IsValid(PlayerCharacter)&& !HitPlayers.Contains(PlayerCharacter))
			{
				PlayerCharacter->TakeDamage(10.f, FDamageEvent(), OwnerController, PawnOwner);
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
}

void UNXNPCAnimInstance::AnimNotify_CheckHit2()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("AnimNotify_CheckHit2 Called!"));
	}
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)return;

	FVector AttackLocation = PawnOwner->GetActorLocation() + PawnOwner->GetActorForwardVector() * 100.f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(NAME_None, false, PawnOwner);

	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		AttackLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(40.f),
		CollisionQueryParams
	);

	if (bResult == true)
	{
		AController* OwnerController = PawnOwner->GetController();
		TSet<AActor*> HitPlayers;

		for (auto const& OverlapResult : OverlapResults)
		{
			ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(OverlapResult.GetActor());
			if (IsValid(PlayerCharacter) && !HitPlayers.Contains(PlayerCharacter))
			{
				PlayerCharacter->TakeDamage(10.f, FDamageEvent(), OwnerController, PawnOwner);
				HitPlayers.Add(PlayerCharacter);
				DrawDebugSphere(GetWorld(), AttackLocation, 40.f, 16, FColor::Green, false, 5.f);
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Hit Player!"));
				}
			}
		}
	}
	else
	{
		DrawDebugSphere(GetWorld(), AttackLocation, 40.f, 16, FColor::Red, false, 5.f);
	}
}