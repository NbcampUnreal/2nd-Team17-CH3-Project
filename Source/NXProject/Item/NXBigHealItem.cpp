#include "NXBigHealItem.h"

ANXBigHealItem::ANXBigHealItem()
{
	HealAmount = 100.0f; //회복량 100으로 설정 (나중에는 체력을 초기화하는 함수를 구현하면 좋을듯)
	ItemType = "Healing";
}

void ANXBigHealItem::ActivateItem(AActor* Activator)
{
	//회복하는 그거 추가
	DestroyItem();
}