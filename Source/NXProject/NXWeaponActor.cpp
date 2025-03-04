#include "NXWeaponActor.h"

ANXWeaponActor::ANXWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComp);
}

