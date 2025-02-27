#include "NXBigHealItem.h"
#include "Player/NXPlayerCharacter.h"

ANXBigHealItem::ANXBigHealItem()
{
	HealAmount = 100.0f; //회복량 100으로 설정 (나중에는 체력을 초기화하는 함수를 구현하면 좋을듯)
	ItemType = "BigHealing";

}


void ANXBigHealItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d HP!"), HealAmount));

        DestroyItem();
    }
}