#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NXWeaponActor.generated.h"

UCLASS()
class NXPROJECT_API ANXWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ANXWeaponActor();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USceneComponent* SceneComp;

};
