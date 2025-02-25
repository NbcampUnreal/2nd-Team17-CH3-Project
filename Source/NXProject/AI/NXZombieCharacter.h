#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "NXZombieCharacter.generated.h"

// 공격 판정을 위한 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckHitDelegate);

UCLASS()
class NXPROJECT_API ANXZombieCharacter : public ANXCharacterBase
{
    GENERATED_BODY()

    friend class UBTTask_Attack;

public:
    ANXZombieCharacter();

protected:
    virtual void BeginPlay() override;

    /** 피격 처리 */
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
        AController* EventInstigator, AActor* DamageCauser) override;

    /** 사망 처리 */
    void Die();
    void DestroyCharacter();

    /** 공격 관련 */
    void BeginAttack();
    void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

    /** 공격 판정 체크 */
    UFUNCTION()
    void HandleCheckHit();

public:
    /** 공격 시작 */
    void StartAttack();

    /** 현재 공격 중인지 확인 */
    bool IsNowAttacking() const { return bIsNowAttacking; }

    /** 공격 델리게이트 */
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCheckHitDelegate OnCheckHitDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackMontage; // 공격 애니메이션

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> DeathMontage; // 사망 애니메이션

    /** 사망 여부 */
    bool bIsDead = false;

    /** 공격 중인지 여부 */
    bool bIsNowAttacking = false;

    /** 사망 후 삭제 타이머 */
    FTimerHandle DeathTimer;
};
