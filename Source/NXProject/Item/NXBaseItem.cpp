#include "NXBaseItem.h"
#include "Components/SphereComponent.h"


ANXBaseItem::ANXBaseItem() //충돌을 위한 컴포넌트 반영
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);
}

void ANXBaseItem::OnItemOverlap(AActor* OverlapActor) //오버랩이 되었을 때
{

}
void ANXBaseItem::OnItemEndOverlap(AActor* OverlapActor) //오버랩이 이후
{

}
void ANXBaseItem::ActivateItem(AActor* Activator) //아이템 사용할 때
{

}
FName ANXBaseItem::GetItemType() const //아이템 이름 식별
{
	return ItemType;
}
