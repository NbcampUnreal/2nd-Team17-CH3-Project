#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "NXPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ANXWeaponActor;
class UWidgetComponent;

struct FInputActionValue;

UCLASS()
class NXPROJECT_API ANXPlayerCharacter : public ANXCharacterBase
{
	GENERATED_BODY()

public:
	ANXPlayerCharacter();

	// ���� UI Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = "UI") // ���⼭ Category�� ���ϴ� ��� ���� ����
		TSubclassOf<UUserWidget> LoseScreenClass; // WBP_LoseScreen

	/*void OnCheckHit();*/
//��
	// ���� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reloading")
	bool bIsReloading;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking")
	bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DashSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* StepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HittedSound;
	
	// NXPlayerCharacter.h
	UFUNCTION(BlueprintPure, Category = "Health")
	virtual float GetHealth() const; // override Ű���� �߰�

	virtual void AddHealth(float Amount) override; // UFUNCTION() �����ϰ� override �߰�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PlayerFireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PlayerReloadAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PlayerHittedAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PlayerDeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAnimation")
	UAnimMontage* AM_PlayerDashForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAnimation")
	UAnimMontage* AM_PlayerDashBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAnimation")
	UAnimMontage* AM_PlayerDashLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAnimation")
	UAnimMontage* AM_PlayerDashRight;

//��

	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnDeath();
	void EnableRagdoll();
	int32 GetHealth();

	float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	);
	void ResetHit();

	TObjectPtr<ANXWeaponActor> GetWeaponInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	//�뽬
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float BackDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashHeight;

	//ũ���ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchTransitionSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CameraLerp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<ANXWeaponActor> WeaponClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<ANXWeaponActor> WeaponInstance;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool GetIsCrouching() const;
	bool bIsCrouching;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//float MaxHealth;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	//float Health;

// 'override' Ű���� ����
	//UFUNCTION(BlueprintPure, Category = "Health")
	//int32 GetHealth() const; // �⺻ Ŭ�������� GetHealth�� �����Ƿ� 'override' ����//��

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTimerHandle CrouchTimerHandle;
	FTimerHandle HitResetTimerHandle;
	FTimerHandle DashCooldownTimerHandle;
	FTimerHandle DashDodgeTimerHandle;
	FTimerHandle FireCoolTimerHandle;
	FTimerHandle ReloadTimerHandle;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartWalk(const FInputActionValue& Value);
	UFUNCTION()
	void StopWalk(const FInputActionValue& Value);
	UFUNCTION()
	void StartCrouch(const FInputActionValue& Value);
	UFUNCTION()
	void StopCrouch(const FInputActionValue& Value);
	UFUNCTION()
	void StartAttack(const FInputActionValue& Value);
	/*UFUNCTION()
	void StopAttack(const FInputActionValue& Value);*/
	UFUNCTION()
	void ResetFire();
	UFUNCTION()
	void Reload();
	UFUNCTION()
	void EndReload();
	/*UFUNCTION()
	void EquipWepon();
	UFUNCTION()
	void UnequipWeapon();*/
	UFUNCTION()
	void Dash();
	void ResetDash();
	void EndDodge();

	void ApplyCrouch();

	void ApplyUnCrouch();

	//����ȭ : NPC �ǰ� �� ��� Ȯ���� ���� �ڵ� �����ص� �������ϴ�-------------------
	/*UFUNCTION()
	void MeleeAttack();*/
	//--------------------
private:
	/*void InputQuickSlot01(const FInputActionValue& Value);
	void InputQuickSlot02(const FInputActionValue& Value);*/

	bool bIsHitted;
	bool bIsDashing;
	bool bIsFire;

	// ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* OverheadWidget;
};
