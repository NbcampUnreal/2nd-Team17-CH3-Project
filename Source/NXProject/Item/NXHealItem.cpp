#include "NXHealItem.h"

ANXHealItem::ANXHealItem()
{
	HealAmount = 30.0f; //회복량 30으로 설정
	ItemType = "Healing";
}

void ANXHealItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}