#include "Weapon/NXShotgun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ANXShotgun::ANXShotgun()
{
	PrimaryActorTick.bCanEverTick = false;

	PelletCount = 10;
	MaxBullet = 5;
	Bullet = MaxBullet;
	MaxRange = 1200.0f;
	MinDamage = 1.0f;
	MaxDamage = 10.0f;
	SpreadAngle = 5.0f;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(SceneComp);
}

void ANXShotgun::FireShotgun()
{
	AActor* WeaponOwner = GetOwner();
	if (!WeaponOwner) return;

	APawn* OwnerPawn = Cast<APawn>(WeaponOwner);
	if (!OwnerPawn)return;

	APlayerController* PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	if (!PlayerController)return;

	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector MuzzleLocation = MeshComp->GetSocketLocation(TEXT("Muzzle"));
	//FRotator MuzzleRotation = MeshComp->GetSocketRotation(TEXT("Muzzle"));

	FVector ShotDirection = CameraRotation.Vector();

	Bullet -= 1;
	for (int32 i = 0;i < PelletCount;i++)
	{
		float SpreadX = FMath::RandRange(-SpreadAngle, SpreadAngle);
		float SpreadY = FMath::RandRange(-SpreadAngle, SpreadAngle);

		FRotator ShotSpread = FRotator(SpreadX, SpreadY, 0);

		FVector FinalDirection = (CameraRotation + ShotSpread).Vector();

		FVector EndLocation = MuzzleLocation + FinalDirection * MaxRange;

		ShotgunTrace(MuzzleLocation, EndLocation);
	}
}

void ANXShotgun::Reloading()
{
	Bullet = MaxBullet;
}

int32 ANXShotgun::GetBullet()
{
	return Bullet;
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
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
	}
}

