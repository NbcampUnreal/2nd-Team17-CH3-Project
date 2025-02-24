#include "Player/NXCharacterBase.h"


ANXCharacterBase::ANXCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

int32 ANXCharacterBase::GetHealth() const
{
	return int32();
}

void ANXCharacterBase::AddHealth(float Amount)
{
}

void ANXCharacterBase::BeginPlay()
{
}

void ANXCharacterBase::OnDeath()
{
}

float ANXCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ANXCharacterBase::Attack()
{
}
