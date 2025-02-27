#include "NXBigHealItem.h"
#include "Player/NXPlayerCharacter.h"
#include "Components/SphereComponent.h"


ANXBigHealItem::ANXBigHealItem()
{
	HealAmount = 100.0f; //회복량 100으로 설정 (나중에는 체력을 초기화하는 함수를 구현하면 좋을듯)
	ItemType = "BigHealing";

}

void ANXBigHealItem::ActivateItem(AActor* Activator)
{
	UE_LOG(LogTemp, Warning, TEXT("오예예ㅖㅖㅖㅖㅖㅖㅖ"));

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
			UE_LOG(LogTemp, Warning, TEXT("오버랩"));
		}

		DestroyItem();
	}
}