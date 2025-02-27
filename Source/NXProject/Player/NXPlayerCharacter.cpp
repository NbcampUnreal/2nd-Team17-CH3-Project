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
//이인화 : 피격 확인을 위해 작성한 코드입니다 삭제하셔도 괜찮습니다 ------------
#include "Engine/OverlapResult.h"
//-----------------
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
	SprintSpeedMultiplier = 1.5f;
	CrouchSpeedMultiplier = 0.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	CrouchSpeed = NormalSpeed * CrouchSpeedMultiplier;
	CrouchTransitionSpeed = 10.0f;
	CameraLerp = 0.0f;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	MaxHealth = 100.0f;
	Health = MaxHealth;

	bIsAttacking = false;
	

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

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ANXPlayerCharacter::StopSprint
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

				EnhancedInput->BindAction(
					PlayerController->AttackAction,
					ETriggerEvent::Completed,
					this,
					&ANXPlayerCharacter::StopAttack
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

			if (PlayerController->QuickSlot01)
			{
				EnhancedInput->BindAction(
					PlayerController->QuickSlot01,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::InputQuickSlot01
				);
			}

			if (PlayerController->QuickSlot02)
			{
				EnhancedInput->BindAction(
					PlayerController->QuickSlot02,
					ETriggerEvent::Triggered,
					this,
					&ANXPlayerCharacter::InputQuickSlot02
				);
			}
		}
	}
}

void ANXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("HP : %f"), Health);
}

void ANXPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetCapsuleHeight = bIsCrouched ? 40.0f : 88.0f;
	float CurrentCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float NewCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, TargetCapsuleHeight, DeltaTime, CrouchTransitionSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewCapsuleHeight, true);
	
	float TargetCameraHeight = bIsCrouched ? 40.0f : 45.0f;
	FVector NewCameraLocation = FMath::VInterpTo(
		CameraComp->GetRelativeLocation(),
		FVector(0, 0, TargetCameraHeight),
		DeltaTime,
		CrouchTransitionSpeed
	);
	CameraComp->SetRelativeLocation(NewCameraLocation);

	float TargetLerp = bIsCrouched ? 0.5f : 0.0f;
	CameraLerp = FMath::FInterpTo(CameraLerp, TargetLerp, DeltaTime, 5.0f);

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

void ANXPlayerCharacter::StartSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ANXPlayerCharacter::StopSprint(const FInputActionValue& Value)
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
	if (GetCharacterMovement()->IsFalling() == true)
	{
		return;
	}

	if (!IsValid(WeaponInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped!"));
		return;
	}

	//이인화 : NPC 피격 및 사망 처리를 확인하기 위한 코드 삭제 가능--------------
	MeleeAttack();
	//-------------
	OnCheckHit();
	bIsAttacking = true;
	
}

void ANXPlayerCharacter::StopAttack(const FInputActionValue& Value)
{
	bIsAttacking = false;
}

void ANXPlayerCharacter::InputQuickSlot01(const FInputActionValue& InValue)
{
	FName WeaponSocket(TEXT("WeaponSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket) == true && IsValid(WeaponInstance) == false)
	{
		WeaponInstance = GetWorld()->SpawnActor<ANXWeaponActor>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(WeaponInstance) == true)
		{
			WeaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		}
	}
}

void ANXPlayerCharacter::InputQuickSlot02(const FInputActionValue& InValue)
{
	if (IsValid(WeaponInstance) == true)
	{
		WeaponInstance->Destroy();
		WeaponInstance = nullptr;
	}
}

void ANXPlayerCharacter::OnCheckHit()
{
	FVector StartLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * 200.0f);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			ANXNonPlayerCharacter* NPC = Cast<ANXNonPlayerCharacter>(HitActor);
			if (NPC)
			{
				FDamageEvent DamageEvent;
				NPC->TakeDamage(20.0f, DamageEvent, GetController(), this);
				UE_LOG(LogTemp, Warning, TEXT("Hit Zombie!"));
			}
		}
	}
}

//숩
float ANXPlayerCharacter::GetHealth() const
{
	return Health;
}

void ANXPlayerCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Log, TEXT("Health increased to: %f"), Health);


}

void ANXPlayerCharacter::OnDeath()
{
	UE_LOG(LogTemp, Error, TEXT("Character is Dead!"));

}
//숩

float ANXPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("Player HP: %.1f / %.1f"), Health, MaxHealth));
	}

	if (Health <= 0.0f)
	{
		OnDeath();
	}
	return ActualDamage;
}


void ANXPlayerCharacter::EquipWepon()
{
	FName WeaponSocket(TEXT("WeaponSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket) && !IsValid(WeaponInstance))
	{
		WeaponInstance = GetWorld()->SpawnActor<ANXWeaponActor>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(WeaponInstance))
		{
			WeaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
			UE_LOG(LogTemp, Log, TEXT("Weapon Equipped"));
		}
	}
}

void ANXPlayerCharacter::UnequipWeapon()
{
	if (IsValid(WeaponInstance))
	{
		WeaponInstance->Destroy();
		WeaponInstance = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Weapon Unequipped"));
	}
}

void ANXPlayerCharacter::Reload(const FInputActionValue& Value)
{
	if (IsValid(WeaponInstance))
	{
		WeaponInstance->ReloadConfig();
		UE_LOG(LogTemp, Log, TEXT("Weapon Reloaded"));
	}
}
//이인화 : NPC 피격 확인을 위해 작성한 코드 삭제해도 괜찮습니다--------
void ANXPlayerCharacter::MeleeAttack()
{
	if (bIsAttacking==true)
	{
		return;
	}
	if (bIsAttacking==false) 
	{
		APawn* PawnOwner = this;
		if (!PawnOwner)return;

		FVector AttackLocation = PawnOwner->GetActorLocation() + PawnOwner->GetActorForwardVector() * 100.f;

		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams CollisionQueryParams(NAME_None, false, PawnOwner);

		bool bResult = GetWorld()->OverlapMultiByChannel(
			OverlapResults,
			AttackLocation,
			FQuat::Identity,
			ECollisionChannel::ECC_Pawn,
			FCollisionShape::MakeSphere(30.f),
			CollisionQueryParams
		);
		if (bResult == true)
		{
			AController* OwnerController = PawnOwner->GetController();
			TSet<AActor*> HitPlayers;

			for (auto const& OverlapResult : OverlapResults)
			{
				ANXNonPlayerCharacter* NPC = Cast<ANXNonPlayerCharacter>(OverlapResult.GetActor());
				if (IsValid(NPC) && !HitPlayers.Contains(NPC))
				{
					NPC->TakeDamage(10.f, FDamageEvent(), OwnerController, PawnOwner);
					HitPlayers.Add(NPC);
					DrawDebugSphere(GetWorld(), AttackLocation, 30.f, 16, FColor::Green, false, 5.f);
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Hit Player!"));
					}
				}
			}
		}
		else
		{
			DrawDebugSphere(GetWorld(), AttackLocation, 30.f, 16, FColor::Red, false, 5.f);
		}
	}
}
//-------------