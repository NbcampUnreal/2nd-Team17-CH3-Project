#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "Game/WaveData.h"
#include "NXSpawner.generated.h"

class UBoxComponent;
class ANXNonPlayerCharacter;

// ������ ���� ������ �����ϴ� ����ü
USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;  // ������ ������ Ŭ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;  // ���� Ȯ��
};

// ���� ���� ������ �����ϴ� ����ü
USTRUCT(BlueprintType)
struct FZombieSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ANXNonPlayerCharacter> ZombieClass;  // ������ ���� Ŭ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;  // ���� Ȯ��
};

UCLASS()
class NXPROJECT_API ANXSpawner : public AActor
{
    GENERATED_BODY()

public:
    ANXSpawner();

    // ���� ������ ����
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomItem();

    // ���� ���� ����
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomZombie();

protected:

    /** ���� **/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    FVector GetRandomPointInVolume() const;

    /** ������ **/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    FItemSpawnRow* GetRandomItem() const;
    void SpawnItem(TSubclassOf<AActor> ItemClass);

    /** ���� **/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ZombieDataTable;

    FZombieSpawnRow* GetRandomZombie() const;
    void SpawnZombie(TSubclassOf<ANXNonPlayerCharacter> ZombieClass);
};
