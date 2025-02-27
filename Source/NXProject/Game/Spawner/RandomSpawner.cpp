#include "RandomSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "AI/NXNonPlayerCharacter.h"
#include "Item/NXBaseItem.h"
#include "GameFramework/Actor.h"

ARandomSpawner::ARandomSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);
}

void ARandomSpawner::BeginPlay()
{
    Super::BeginPlay();

    SpawnRandomActor();
}

void ARandomSpawner::SpawnRandomActor()
{
    DestroyActor();

    if (SpawnableItems.Num() > 0 || SpawnableZombies.Num() > 0)
    {
        // 50% 확률로 아이템 또는 좀비 스폰
        bool bSpawnZombie = FMath::RandBool();

        TArray<FSpawnData> SpawnableActors = bSpawnZombie ? SpawnableZombies : SpawnableItems;
        if (SpawnableActors.Num() > 0)
        {
            float TotalChance = 0.0f;
            for (const FSpawnData& ActorData : SpawnableActors)
            {
                TotalChance += ActorData.SpawnChance;
            }

            float RandomValue = FMath::FRandRange(0.0f, TotalChance);
            float AccumulatedChance = 0.0f;

            for (const FSpawnData& ActorData : SpawnableActors)
            {
                AccumulatedChance += ActorData.SpawnChance;

                if (RandomValue <= AccumulatedChance)
                {
                    if (ActorData.ActorClass)
                    {
                        FVector SpawnLocation = GetRandomPointInVolume();

                        CurrentSpawnedActor = GetWorld()->SpawnActor<AActor>(
                            ActorData.ActorClass,
                            SpawnLocation,
                            FRotator::ZeroRotator
                        );

                        UE_LOG(LogTemp, Warning, TEXT("Spawned Actor: %s at Location: %s"),
                            *ActorData.ActorClass->GetName(),
                            *SpawnLocation.ToString());

                        break;
                    }
                }
            }
        }
    }
}

FVector ARandomSpawner::GetRandomPointInVolume() const
{
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

void ARandomSpawner::DestroyActor()
{
    if (IsValid(CurrentSpawnedActor))
    {
        CurrentSpawnedActor->Destroy();
        CurrentSpawnedActor = nullptr;
    }
}
