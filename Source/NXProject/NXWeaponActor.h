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

	//USkeletalMeshComponent* GetMesh() const { return Mesh; }

protected:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> Mesh;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USceneComponent* SceneComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//USkeletalMeshComponent* Mesh;
};
