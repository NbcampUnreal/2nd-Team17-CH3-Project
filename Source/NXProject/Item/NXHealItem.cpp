#include "NXHealItem.h"

ANXHealItem::ANXHealItem()
{
	HealAmount = 30.0f; //회복량 30으로 설정
	ItemType = "Healing";
}

void ANXHealItem::ActivateItem(AActor* Activator)
{
	//힐링하는 회복 로직 추가해야함
	DestroyItem();
}