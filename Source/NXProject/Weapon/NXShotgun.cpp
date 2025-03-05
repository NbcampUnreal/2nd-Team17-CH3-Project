#include "Weapon/NXShotgun.h"
#include "Kismet/GameplayStatics.h"

ANXShotgun::ANXShotgun()
	:PelletCount(10),
	MaxBullet(8),
	Bullet(MaxBullet),
	MaxRange(1200.0f),
	MinDamage(1.0f),
	MaxDamage(10.0f),
	SpreadAngle(5.0f)
{
	PrimaryActorTick.bCanEverTick = false;

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

	FVector ShotDirection = CameraRotation.Vector();

	Bullet -= 1;

	if (MuzzleFlash)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			MuzzleFlash,
			MuzzleLocation,
			CameraRotation
		);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, MuzzleLocation);
	}

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
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ANXShotgun::Reload,
		3.0f,
		false
	);
}

void ANXShotgun::Reload()
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

		}
	}
}

