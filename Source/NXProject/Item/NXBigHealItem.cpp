#include "NXBigHealItem.h"
#include "Player/NXPlayerCharacter.h"
#include "Components/SphereComponent.h"


ANXBigHealItem::ANXBigHealItem()
{
	HealAmount = 100.0f; //회복량 100으로 설정 (나중에는 체력을 초기화하는 함수를 구현하면 좋을듯)
	ItemType = "BigHealing";

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OnActorBeginOverlap.AddDynamic(this, &ANXBigHealItem::OnOverlapBegin);



}

void ANXBigHealItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("오예"));

	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{

		DestroyItem();
	}
}

void ANXBigHealItem::ActivateItem(AActor* Activator)
{
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