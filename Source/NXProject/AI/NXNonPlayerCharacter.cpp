
#include "AI/NXNonPlayerCharacter.h"
#include "AI/NXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Engine/Engine.h"
#include "Game/NXGameState.h"
#include "Game/NXGameInstance.h"



ANXNonPlayerCharacter::ANXNonPlayerCharacter()
{
	AIControllerClass = ANXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	bIsDead = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	MaxHealth = 100.0f;
	Health = MaxHealth;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::World);

}

void ANXNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverheadHP();
}

void ANXNonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OverheadWidget)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			FVector PlayerLocation = PlayerCharacter->GetActorLocation();
			FVector WidgetLocation = OverheadWidget->GetComponentLocation();

			FRotator LookAtRotation = (PlayerLocation - WidgetLocation).Rotation();
			OverheadWidget->SetWorldRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));

			float Distance = FVector::Dist(PlayerLocation, WidgetLocation);
			float ScaleFactor = FMath::Clamp(Distance / 500.f, 0.5f, 1.5f);
			OverheadWidget->SetWorldScale3D(FVector(ScaleFactor));

		}
	}
}

int32 ANXNonPlayerCharacter::GetHealth() const
{
	return Health;
}

void ANXNonPlayerCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget)
	{
		return;
	}

	if (UUserWidget* WidgetInstance = OverheadWidget->GetUserWidgetObject())
	{
		if (UProgressBar* HPBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("OverHeadHPBar"))))
		{
			const float HPPercent = (MaxHealth > 0.f) ? Health / MaxHealth : 0.f;
			HPBar->SetPercent(HPPercent);
			
		}
	}
}

float ANXNonPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead)
	{
		return 0.f;
	}
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (ActualDamage > 0.f)
	{
		Health = FMath::Clamp(Health - ActualDamage, 0.0f, MaxHealth);
		if (GetMesh() && GetMesh()->GetAnimInstance())
		{
			//피격 애니메이션 실행
			GetMesh()->GetAnimInstance()->Montage_Play(NPCHittedAnimation,1.f);
		}
		UpdateOverheadHP();

		if (Health <= 0.0f)
		{
			OnDeath();
		}
	}
	return ActualDamage;
}

void ANXNonPlayerCharacter::OnDeath()
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;

	ANXAIController* AIController = Cast<ANXAIController>(GetController());
	if (IsValid(AIController))
	{
			AIController->EndAI();
	}
	if (GetMesh() && GetMesh()->GetAnimInstance())
	{
		//사망 애니메이션 실행
		GetMesh()->GetAnimInstance()->Montage_Play(NPCDeadAnimation,1.f);
	}
	SetLifeSpan(1.5f);
	if (UWorld* World = GetWorld())
	{
		if (ANXGameState* GameState = World->GetGameState<ANXGameState>())
		{
			GameState->AddScore(1);
		}
	}

}