// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NXNonPlayerCharacter.h"
#include "NXBossZombie.generated.h"

// 전방 선언
class UWidgetComponent;
class UUserWidget;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* LandSound;

	// 보스가 죽을 때 호출되는 함수
	void OnDeath();

	// 엔딩 UI 클래스
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> WinScreenClass; // WBP_WinScreen

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
