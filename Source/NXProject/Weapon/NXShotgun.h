
#pragma once

#include "CoreMinimal.h"
#include "NXProject/NXWeaponActor.h"
#include "NXShotgun.generated.h"

UCLASS()
class NXPROJECT_API ANXShotgun : public ANXWeaponActor
{
	GENERATED_BODY()

public:
	ANXShotgun();

	void FireShotgun();
	void Reloading();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	int32 Bullet;
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	int32 MaxBullet;

	int32 GetBullet();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	int32 PelletCount;//»êÅº °¹¼ö
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	float MaxRange;
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	float MinDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	float MaxDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Shotgun")
	float SpreadAngle;

	void ShotgunTrace(FVector Start, FVector End);
};
