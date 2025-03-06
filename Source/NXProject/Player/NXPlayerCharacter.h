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

	// 엔딩 UI 클래스
	UPROPERTY(EditDefaultsOnly, Category = "UI") // 여기서 Category는 원하는 대로 변경 가능
		TSubclassOf<UUserWidget> LoseScreenClass; // WBP_LoseScreen

	/*void OnCheckHit();*/
//숩
	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// 최대 체력
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
	virtual float GetHealth() const; // override 키워드 추가

	virtual void AddHealth(float Amount) override; // UFUNCTION() 제거하고 override 추가

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

//숩

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

	//무브
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	//대쉬
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float BackDashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashHeight;

	//크라우치
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

// 'override' 키워드 제거
	//UFUNCTION(BlueprintPure, Category = "Health")
	//int32 GetHealth() const; // 기본 클래스에서 GetHealth가 없으므로 'override' 제거//숩

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

	//이인화 : NPC 피격 및 사망 확인을 위한 코드 삭제해도 괜찮습니다-------------------
	/*UFUNCTION()
	void MeleeAttack();*/
	//--------------------
private:
	/*void InputQuickSlot01(const FInputActionValue& Value);
	void InputQuickSlot02(const FInputActionValue& Value);*/

	bool bIsHitted;
	bool bIsDashing;
	bool bIsFire;

	// 위젯 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* OverheadWidget;
};
