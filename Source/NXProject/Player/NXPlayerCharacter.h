#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "NXPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ANXWeaponActor;

struct FInputActionValue;

UCLASS()
class NXPROJECT_API ANXPlayerCharacter : public ANXCharacterBase
{
	GENERATED_BODY()

public:
	ANXPlayerCharacter();

	void OnCheckHit();
//숩
	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	// NXPlayerCharacter.h
	UFUNCTION(BlueprintPure, Category = "Health")
	virtual float GetHealth() const; // override 키워드 추가

	virtual void AddHealth(float Amount) override; // UFUNCTION() 제거하고 override 추가




//숩

	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnDeath();

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchTransitionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CameraLerp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSubclassOf<ANXWeaponActor> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<ANXWeaponActor> WeaponInstance;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool GetIsCrouching() const;
	bool bIsCrouching;
	bool bIsAttacking;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//float MaxHealth;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	//float Health;

// 'override' 키워드 제거
	//UFUNCTION(BlueprintPure, Category = "Health")
	//int32 GetHealth() const; // 기본 클래스에서 GetHealth가 없으므로 'override' 제거//숩

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTimerHandle CrouchTimerHandle;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);
	UFUNCTION()
	void StartCrouch(const FInputActionValue& Value);
	UFUNCTION()
	void StopCrouch(const FInputActionValue& Value);
	UFUNCTION()
	void StartAttack(const FInputActionValue& Value);
	UFUNCTION()
	void StopAttack(const FInputActionValue& Value);
	UFUNCTION()
	void Reload(const FInputActionValue& Value);
	UFUNCTION()
	void EquipWepon();
	UFUNCTION()
	void UnequipWeapon();

	void ApplyCrouch();

	void ApplyUnCrouch();
	//이인화 : NPC 피격 및 사망 확인을 위한 코드 삭제해도 괜찮습니다-------------------
	UFUNCTION()
	void MeleeAttack();
	//--------------------
private:
	void InputQuickSlot01(const FInputActionValue& Value);
	void InputQuickSlot02(const FInputActionValue& Value);


};
