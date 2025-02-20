#include "NXBaseItem.h"


ANXBaseItem::ANXBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANXBaseItem::OnItemOverlap(AActor* OverlapActor)
{

}
void ANXBaseItem::OnItemEndOverlap(AActor* OverlapActor)
{

}
void ANXBaseItem::ActivateItem(AActor* Activator)
{

}
FName ANXBaseItem::GetItemType() const
{
	return ItemType;
}
