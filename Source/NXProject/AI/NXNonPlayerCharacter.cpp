// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NXNonPlayerCharacter.h"
#include "AI/NXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ANXNonPlayerCharacter::ANXNonPlayerCharacter()
{
	AIControllerClass = ANXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WalkSpeed = 100.f;
	RunSpeed = 300.f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
