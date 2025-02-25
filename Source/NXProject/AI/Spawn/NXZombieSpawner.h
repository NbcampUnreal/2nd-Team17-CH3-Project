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

    /** ���� �ڽ� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    /** ���� Ŭ���� (������ ���� ����) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<ANXZombieCharacter> ZombieClass;  // ZombieClass �߰�

    /** ���� ��ġ �迭 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TArray<FVector> SpawnLocations;  // SpawnLocations �߰�

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    FVector GetRandomPointInVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnZombie();

    /** ���� �ð����� ���� ���� */
    void StartSpawning();

protected:
    virtual void BeginPlay() override;

private:
    /** ���� ���� Ÿ�̸� */
    FTimerHandle SpawnTimerHandle;
};
