#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NXGrenadeWeapon.generated.h"

UCLASS()
class NXPROJECT_API ANXGrenadeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ANXGrenadeWeapon();

	virtual void Tick(float DeltaTime) override;
	void Initialize(float Damage, float FuseTime); //수류탄 데미지와 폭발 시간

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* GrenadeMesh; 

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float DamageAmount; //수류탄의 데미지

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FuseTime; //폭발하기까지 걸리는 시간

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Explode(); //폭발

protected:
	virtual void BeginPlay() override;
};
