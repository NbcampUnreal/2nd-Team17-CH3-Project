#include "NXHealItem.h"
#include "Player/NXPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ANXHealItem::ANXHealItem()
{
	HealAmount = 30.0f; //회복량 30으로 설정
	ItemType = "Healing";

}


void ANXHealItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			HealingEffect,
			GetActorLocation(),
			GetActorRotation()
		);

		if (HealSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HealSound, GetActorLocation());
		}

		DestroyItem();
	}
}
