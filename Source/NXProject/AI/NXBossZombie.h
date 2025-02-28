// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NXNonPlayerCharacter.h"
#include "NXBossZombie.generated.h"


UCLASS()
class NXPROJECT_API ANXBossZombie : public ANXNonPlayerCharacter
{
	GENERATED_BODY()
public:
	ANXBossZombie();
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;
	bool bIsJumpAttacking = false;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAttack")
	float JumpAttackRadius = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAttack")
	float JumpAttackDamage = 50.f;
};
