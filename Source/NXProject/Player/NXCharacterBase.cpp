#include "Player/NXCharacterBase.h"


ANXCharacterBase::ANXCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANXCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ANXCharacterBase::AddHealth(float Amount)
{
}

