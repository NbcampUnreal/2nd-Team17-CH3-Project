#include "AI/Spawn/NXZombieSpawner.h"
#include "AI/NXZombieCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

ANXZombieSpawner::ANXZombieSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);
}

void ANXZombieSpawner::BeginPlay()
{
    Super::BeginPlay();

    // ZombieClass�� �������� �ʾҴٸ� �⺻���� �Ҵ� (�ɼ�)
    if (!ZombieClass) {
        ZombieClass = ANXZombieCharacter::StaticClass(); // �⺻ ���� Ŭ���� ����
    }

    // SpawnLocations �ʱ�ȭ ����
    if (SpawnLocations.Num() == 0) {
        SpawnLocations.Add(FVector(100.f, 200.f, 300.f));
        SpawnLocations.Add(FVector(200.f, 300.f, 400.f));
    }

    StartSpawning();
}

void ANXZombieSpawner::StartSpawning()
{
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANXZombieSpawner::SpawnZombie, 5.0f, true);
}

FVector ANXZombieSpawner::GetRandomPointInVolume() const
{
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

void ANXZombieSpawner::SpawnZombie()
{
    // ZombieClass�� SpawnLocations �迭�� ��ȿ���� Ȯ��
    if (ZombieClass && SpawnLocations.Num() > 0)
    {
        int32 Index = UKismetMathLibrary::RandomIntegerInRange(0, SpawnLocations.Num() - 1);
        FVector SpawnLocation = SpawnLocations[Index];

        // ���� ����
        GetWorld()->SpawnActor<AActor>(ZombieClass, SpawnLocation, FRotator::ZeroRotator);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ZombieClass or SpawnLocations is invalid!"));
    }
}
