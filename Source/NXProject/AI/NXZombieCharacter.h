#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "EnhancedInputComponent.h" // ��ǲ ��� �߰��� 1.4 ��Ÿ�� ����
#include "NXZombieCharacter.generated.h"

//DECLARE_DELEGATE_TwoParams(FOnAttackMontageEnded, UAnimMontage*, bool /*bInterrupted*/)

class UAnimMontage;

UCLASS()
class NXPROJECT_API ANXZombieCharacter : public ANXCharacterBase
{
	GENERATED_BODY()

	friend class UBTTask_Attack;
	
public:
	ANXZombieCharacter();

	// ���� ����
	void StartAttack();  // StartAttack �޼��带 public���� ����

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Intpu, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UFUNCTION()
	void OnCheckHit();

 // ���� ������ �����ϴ� protected �޼���
    void BeginAttack();  // BeginAttack�� ������ protected�� �ξ� ���� ȣ�� �Ұ�

	/** ���� ���� �Լ� (���� �߰�) */
	void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

	bool bIsNowAttacking;

public:
	bool IsNowAttacking() const { return bIsNowAttacking; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> AttackMontage;
	// �翬�� �̾߱�����, BP_NPC > Details > AttackMontage AM_TestAttack ���� �ʼ�.

	//FOnAttackMontageEnded OnAttackMontageEndedDelegate;
	// �ִϸ��̼� ��Ÿ�� ����� ������ �� ȣ���� ��������Ʈ.

};
