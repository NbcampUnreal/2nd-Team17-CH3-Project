#include "NXHealItem.h"
#include "Player/NXPlayerCharacter.h"
#include "Components/SphereComponent.h"

ANXHealItem::ANXHealItem()
{
	HealAmount = 30.0f; //회복량 30으로 설정
	ItemType = "Healing";

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	OnActorBeginOverlap.AddDynamic(this, &ANXHealItem::OnOverlapBegin);

}

void ANXHealItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("오예"));

	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{

		DestroyItem();
	}
}

void ANXHealItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ANXPlayerCharacter* PlayerCharacter = Cast<ANXPlayerCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}

		DestroyItem();
	}
}
