
#include "AI/NXNonPlayerCharacter.h"
#include "AI/NXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Engine/Engine.h"


ANXNonPlayerCharacter::ANXNonPlayerCharacter()
{
	AIControllerClass = ANXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	MaxHealth = 100.0f;
	Health = MaxHealth;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

void ANXNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverheadHP();
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
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("HP Updated: %f"), HPPercent));
			}
		}
	}
}

float ANXNonPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
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

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("NPC Hit! Health: %f"), Health));
		}

		if (Health <= 0.0f)
		{
			OnDeath();
		}
	}
	return ActualDamage;
}

void ANXNonPlayerCharacter::OnDeath()
{
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
	SetLifeSpan(3.f);

}