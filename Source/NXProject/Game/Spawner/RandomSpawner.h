#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI/NXNonPlayerCharacter.h"
#include "Item/NXBaseItem.h"
#include "RandomSpawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawnData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float SpawnChance = 50.0f;
};

class UBoxComponent;

UCLASS()
class NXPROJECT_API ARandomSpawner : public AActor

{
    GENERATED_BODY()

public:
    ARandomSpawner();

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TArray<FSpawnData> SpawnableItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TArray<FSpawnData> SpawnableZombies;

    UPROPERTY()
    AActor* CurrentSpawnedActor;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomActor();

    UFUNCTION(BlueprintPure, Category = "Spawning")
    FVector GetRandomPointInVolume() const;

private:
    void DestroyActor();
};
