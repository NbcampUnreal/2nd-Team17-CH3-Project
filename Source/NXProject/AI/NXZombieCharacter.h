#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "NXZombieCharacter.generated.h"

// ���� ������ ���� ��������Ʈ ����
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

    /** �ǰ� ó�� */
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
        AController* EventInstigator, AActor* DamageCauser) override;

    /** ��� ó�� */
    void Die();
    void DestroyCharacter();

    /** ���� ���� */
    void BeginAttack();
    void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

    /** ���� ���� üũ */
    UFUNCTION()
    void HandleCheckHit();

public:
    /** ���� ���� */
    void StartAttack();

    /** ���� ���� ������ Ȯ�� */
    bool IsNowAttacking() const { return bIsNowAttacking; }

    /** ���� ��������Ʈ */
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCheckHitDelegate OnCheckHitDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackMontage; // ���� �ִϸ��̼�

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> DeathMontage; // ��� �ִϸ��̼�

    /** ��� ���� */
    bool bIsDead = false;

    /** ���� ������ ���� */
    bool bIsNowAttacking = false;

    /** ��� �� ���� Ÿ�̸� */
    FTimerHandle DeathTimer;
};
