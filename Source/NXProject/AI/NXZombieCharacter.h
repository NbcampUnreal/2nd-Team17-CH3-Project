#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "EnhancedInputComponent.h" // 인풋 헤더 추가함 1.4 몽타주 로직
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

	// 공격 시작
	void StartAttack();  // StartAttack 메서드를 public으로 선언

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Intpu, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UFUNCTION()
	void OnCheckHit();

 // 실제 공격을 시작하는 protected 메서드
    void BeginAttack();  // BeginAttack은 여전히 protected로 두어 직접 호출 불가

	/** 공격 종료 함수 (선언 추가) */
	void EndAttack(UAnimMontage* InMontage, bool bInterrupted);

	bool bIsNowAttacking;

public:
	bool IsNowAttacking() const { return bIsNowAttacking; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> AttackMontage;
	// 당연한 이야기지만, BP_NPC > Details > AttackMontage AM_TestAttack 지정 필수.

	//FOnAttackMontageEnded OnAttackMontageEndedDelegate;
	// 애니메이션 몽타주 재생이 끝났을 때 호출할 델리게이트.

};
