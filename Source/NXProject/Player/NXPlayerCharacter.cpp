#include "Player/NXPlayerCharacter.h"
#include "Player/NXPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "NXWeaponActor.h"
#include "AI/NXZombieCharacter.h"
#include "AI/NXNonPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "Engine/Engine.h"
#include "Engine/OverlapResult.h"
#include "Weapon/NXShotgun.h"
ANXPlayerCharacter::ANXPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	WalkSpeedMultiplier = 0.5f;
	CrouchSpeedMultiplier = 0.4f;
	WalkSpeed = NormalSpeed * WalkSpeedMultiplier;
	CrouchSpeed = NormalSpeed * CrouchSpeedMultiplier;

	DashSpeed = 900.0f;
	BackDashSpeed = 600.0f;
	DashHeight = 250.0f;

	CrouchTransitionSpeed = 2.0f;
	CameraLerp = 0.0f;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	MaxHealth = 100.0f;
	Health = MaxHealth;



	bIsAttacking = false;
	bIsDashing = false;
	bIsFire = false;

}

void ANXPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ANXPlayerController* PlayerController = Cast<ANXPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ANXPlayerCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::Look
				);
			}

			if (PlayerController->WalkAction)
			{
				EnhancedInput->BindAction(
					PlayerController->WalkAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::StartWalk
				);

				EnhancedInput->BindAction(
					PlayerController->WalkAction,
					ETriggerEvent::Completed,
					this,
					&ANXPlayerCharacter::StopWalk
				);
			}

			if (PlayerController->CrouchAction)
			{
				EnhancedInput->BindAction(
					PlayerController->CrouchAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::StartCrouch
				);

				EnhancedInput->BindAction(
					PlayerController->CrouchAction,
					ETriggerEvent::Completed,
					this,
					&ANXPlayerCharacter::StopCrouch
				);
			}

			if (PlayerController->AttackAction)
			{
				EnhancedInput->BindAction(
					PlayerController->AttackAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::StartAttack
				);
			}

			if (PlayerController->ReloadAction)
			{
				EnhancedInput->BindAction(
					PlayerController->ReloadAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::Reload
				);
			}

			if (PlayerController->DashAction)
			{
				EnhancedInput->BindAction(
					PlayerController->DashAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::Dash
				);
			}
		}
	}
}

void ANXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponClass)
	{
		WeaponInstance = GetWorld()->SpawnActor<ANXWeaponActor>(WeaponClass);
		if (WeaponInstance)
		{
			WeaponInstance->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				TEXT("WeaponSocket"));
		}
	}
	WeaponInstance->SetOwner(this);
}

void ANXPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetCapsuleHeight = bIsCrouched ? 40.0f : 88.0f;
	float CurrentCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float NewCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, TargetCapsuleHeight, DeltaTime, CrouchTransitionSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewCapsuleHeight, true);

}

void ANXPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}

}

void ANXPlayerCharacter::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (bIsDashing) return;
		Jump();
	}
}

void ANXPlayerCharacter::StopJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		StopJumping();
	}
}

void ANXPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);

}

void ANXPlayerCharacter::StartWalk(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ANXPlayerCharacter::StopWalk(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void ANXPlayerCharacter::StartCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Crouch();
		bIsCrouching = true;
	}
	GetWorld()->GetTimerManager().SetTimer(CrouchTimerHandle, this, &ANXPlayerCharacter::ApplyCrouch, 0.05f, true);
}

void ANXPlayerCharacter::StopCrouch(const FInputActionValue& Value)
{
	if (bIsCrouched)
	{
		UnCrouch();
		bIsCrouching = false;
	}
	GetWorld()->GetTimerManager().SetTimer(CrouchTimerHandle, this, &ANXPlayerCharacter::ApplyUnCrouch, 0.05f, true);
}

void ANXPlayerCharacter::ApplyCrouch()
{
	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
	float NewSpeed = FMath::FInterpTo(CurrentSpeed, CrouchSpeed, GetWorld()->GetDeltaSeconds(), 5.0f);
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

	if (FMath::IsNearlyEqual(NewSpeed, CrouchSpeed, 1.0f))
	{
		GetWorld()->GetTimerManager().ClearTimer(CrouchTimerHandle);
	}
}

void ANXPlayerCharacter::ApplyUnCrouch()
{
	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
	float NewSpeed = FMath::FInterpTo(CurrentSpeed, NormalSpeed, GetWorld()->GetDeltaSeconds(), 5.0f);
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

	if (FMath::IsNearlyEqual(NewSpeed, NormalSpeed, 1.0f))
	{
		GetWorld()->GetTimerManager().ClearTimer(CrouchTimerHandle);
	}
}


bool ANXPlayerCharacter::GetIsCrouching() const
{
	return bIsCrouched;
}

void ANXPlayerCharacter::StartAttack(const FInputActionValue& Value)
{
	if (bIsDashing) return;

	if (bIsFire)return;

	if (WeaponInstance && WeaponInstance->IsA(ANXShotgun::StaticClass()))
	{
		ANXShotgun* Shotgun = Cast<ANXShotgun>(WeaponInstance);

		if (Shotgun && Shotgun->GetBullet() > 1)
		{
			if (GetMesh() && GetMesh()->GetAnimInstance())
			{
				GetMesh()->GetAnimInstance()->Montage_Play(PlayerFireAnimation, 1.f);
			}

			Shotgun->FireShotgun();
			bIsFire = true;
			GetWorldTimerManager().SetTimer(
				FireCoolTimerHandle,
				this,
				&ANXPlayerCharacter::ResetFire,
				0.5f,
				false
			);
		}
		else if (Shotgun && Shotgun->GetBullet() <= 1)
		{
			if (GetMesh() && GetMesh()->GetAnimInstance())
			{
				GetMesh()->GetAnimInstance()->Montage_Play(PlayerFireAnimation, 1.f);
			}

			Shotgun->FireShotgun();
			Reload();
		}
	}
}
void ANXPlayerCharacter::ResetFire()
{
	bIsFire = false;
}


//¼ü
float ANXPlayerCharacter::GetHealth() const
{
	return Health;
}

void ANXPlayerCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);


}

void ANXPlayerCharacter::OnDeath()
{
	if (GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(PlayerDeathAnimation, 1.f);
	}

}
//¼ü

float ANXPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsHitted)return 0.0f;

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(PlayerHittedAnimation, 1.f);
	}

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	if (Health <= 0.0f)
	{
		OnDeath();
	}
	bIsHitted = true;

	GetWorldTimerManager().SetTimer(HitResetTimerHandle, this, &ANXPlayerCharacter::ResetHit, 0.5f, false);

	return ActualDamage;
}
void ANXPlayerCharacter::ResetHit()
{
	bIsHitted = false;
}


void ANXPlayerCharacter::Dash()
{
	if (bIsDashing) return;

	FVector InputDirection = GetLastMovementInputVector();
	InputDirection = InputDirection.GetSafeNormal();

	UAnimMontage* PlayerDashAnimation = nullptr;
	FVector DashVelocity = FVector::ZeroVector;

	if (FVector::DotProduct(InputDirection, GetActorForwardVector()) > 0.7f)
	{
		PlayerDashAnimation = AM_PlayerDashForward;
		DashVelocity = GetActorForwardVector() * DashSpeed;
	}
	else if (FVector::DotProduct(InputDirection, GetActorForwardVector()) < -0.7f)
	{
		PlayerDashAnimation = AM_PlayerDashBack;
		DashVelocity = -GetActorForwardVector() * BackDashSpeed;
	}
	else if (FVector::DotProduct(InputDirection, GetActorRightVector()) > 0.7f)
	{
		PlayerDashAnimation = AM_PlayerDashRight;
		DashVelocity = GetActorRightVector() * DashSpeed;
	}
	else if (FVector::DotProduct(InputDirection, GetActorRightVector()) < -0.7f)
	{
		PlayerDashAnimation = AM_PlayerDashLeft;
		DashVelocity = -GetActorRightVector() * DashSpeed;
	}

	if (PlayerDashAnimation && GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(PlayerDashAnimation, 1.f);
	}

	DashVelocity.Z = DashHeight;
	LaunchCharacter(DashVelocity, true, true);
	bIsHitted = true;
	GetWorldTimerManager().SetTimer(DashDodgeTimerHandle, this, &ANXPlayerCharacter::EndDodge, 0.4f, false);

	bIsDashing = true;
	GetWorldTimerManager().SetTimer(DashCooldownTimerHandle, this, &ANXPlayerCharacter::ResetDash, 1.0f, false);
}

void ANXPlayerCharacter::ResetDash()
{
	bIsDashing = false;
}

void ANXPlayerCharacter::EndDodge()
{
	bIsHitted = false;
}

void ANXPlayerCharacter::Reload()
{
	if (IsValid(WeaponInstance))
	{
		if (bIsReloading)return;
		if (GetMesh() && GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(PlayerReloadAnimation, 1.f);
		}
		bIsFire = true;
		GetWorldTimerManager().SetTimer(
			FireCoolTimerHandle,
			this,
			&ANXPlayerCharacter::ResetFire,
			3.0f,
			false
		);
		bIsReloading = true;
		GetWorldTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&ANXPlayerCharacter::EndReload,
			3.0f,
			false
		);
		if (WeaponInstance && WeaponInstance->IsA(ANXShotgun::StaticClass()))
		{
			Cast<ANXShotgun>(WeaponInstance)->Reloading();
		}
	}
}
void ANXPlayerCharacter::EndReload()
{
	bIsReloading = false;
}