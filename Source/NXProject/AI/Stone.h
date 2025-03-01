
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stone.generated.h"

class UProjectileMovementComponent;
class ANXAIController;
class ANXBossZombie;

UCLASS()
class NXPROJECT_API AStone : public AActor
{
	GENERATED_BODY()
	
public:	
	AStone();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Projectile")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void SetOwnerInfo(ANXAIController* Controller, ANXBossZombie* Boss);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 2000.0f;
	float StoneDamage = 20.0f;
	
private:
	UPROPERTY()
	ANXAIController* OwnerController;

	UPROPERTY()
	ANXBossZombie* PawnOwner;
};
