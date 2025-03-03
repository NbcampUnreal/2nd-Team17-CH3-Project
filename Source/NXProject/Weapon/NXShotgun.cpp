#include "Weapon/NXShotgun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ANXShotgun::ANXShotgun()
{
	PrimaryActorTick.bCanEverTick = false;

	PelletCount = 10;
	MaxBullet = 5;
	Bullet = MaxBullet;
	MaxRange = 1500.0f;
	MinDamage = 1.0f;
	MaxDamage = 10.0f;
	SpreadAngle = 10.0f;

}

void ANXShotgun::FireShotgun()
{
	AActor* WeaponOwner = GetOwner();
	if (!WeaponOwner) return;
	FVector MuzzleLocation = WeaponOwner->GetActorLocation() + FVector(50, 0, 50);
	FRotator MuzzleRotation = WeaponOwner->GetActorRotation();
	
	for (int32 i = 0;i < PelletCount;i++)
	{
		float SpreadX = FMath::RandRange(-SpreadAngle, SpreadAngle);
		float SpreadY = FMath::RandRange(-SpreadAngle, SpreadAngle);

		FRotator ShotDirection = MuzzleRotation + FRotator(SpreadX, SpreadY, 0);
		FVector EndLocation = MuzzleLocation + ShotDirection.Vector() * MaxRange;

		ShotgunTrace(MuzzleLocation, EndLocation);
	}
}

void ANXShotgun::ShotgunTrace(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			float Distance = FVector::Dist(Start, HitResult.ImpactPoint);
			float Damage = FMath::Lerp(MaxDamage, MinDamage, Distance / MaxRange);

			UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
		}
	}
}