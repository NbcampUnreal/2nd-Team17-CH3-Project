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
	UFUNCTION()
	void DashAttack();
	UFUNCTION()
	void StopDash();
	UFUNCTION()
	void OnDashHit();

	bool bIsJumpAttacking = false;
	bool bIsDashAttacking = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "DashAttack")
	FVector DashDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* BossJumpAttackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* BossJumpAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* BossDashAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAttack")
	float JumpAttackRadius = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAttack")
	float JumpAttackDamage = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JumpAttack")
	float DashAttackDamage = 30.f;

	FTimerHandle DashHitTimer;
	FTimerHandle DashEndTimer;
};
