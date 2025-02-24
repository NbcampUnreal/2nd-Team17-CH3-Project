#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "NXZombieSpawner.generated.h"

class UBoxComponent;
class ANXZombieCharacter;

UCLASS()
class NXPROJECT_API ANXZombieSpawner : public AActor
{
    GENERATED_BODY()

public:
    ANXZombieSpawner();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    /** 스폰 박스 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    /** 좀비 클래스 (스폰할 좀비 종류) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<ANXZombieCharacter> ZombieClass;  // ZombieClass 추가

    /** 스폰 위치 배열 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TArray<FVector> SpawnLocations;  // SpawnLocations 추가

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    FVector GetRandomPointInVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnZombie();

    /** 일정 시간마다 좀비 스폰 */
    void StartSpawning();

protected:
    virtual void BeginPlay() override;

private:
    /** 좀비 스폰 타이머 */
    FTimerHandle SpawnTimerHandle;
};
