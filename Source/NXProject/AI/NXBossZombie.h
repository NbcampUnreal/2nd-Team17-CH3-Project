// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NXNonPlayerCharacter.h"
#include "NXBossZombie.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API ANXBossZombie : public ANXNonPlayerCharacter
{
	GENERATED_BODY()
public:
	ANXBossZombie();
private:
	bool bIsJumpAttacking = false;
	float JumpAttackRadius = 300.f;
	float JumpAttackDamage = 50.f;
};
