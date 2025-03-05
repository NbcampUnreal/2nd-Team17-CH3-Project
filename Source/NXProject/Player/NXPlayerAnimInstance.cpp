// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NXPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NXPlayerCharacter.h"

void UNXPlayerAnimInstance::AnimNotify_AN_FootPlant_Left()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)return;

	ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(PawnOwner);

	if (PlayerCharacter && PlayerCharacter->StepSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PlayerCharacter->StepSound, PlayerCharacter->GetActorLocation());
	}
}

void UNXPlayerAnimInstance::AnimNotify_AN_FootPlant_Right()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)return;

	ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(PawnOwner);

	if (PlayerCharacter && PlayerCharacter->StepSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PlayerCharacter->StepSound, PlayerCharacter->GetActorLocation());
	}
}
