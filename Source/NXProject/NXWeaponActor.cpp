#include "NXWeaponActor.h"

ANXWeaponActor::ANXWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	/*Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	*/
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComp);

	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(SceneComp);

	//Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

