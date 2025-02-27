#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "Game/WaveData.h"
#include "NXSpawner.generated.h"

class UBoxComponent;
class ANXNonPlayerCharacter;

// 아이템 스폰 정보를 저장하는 구조체
USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;  // 스폰할 아이템 클래스

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;  // 스폰 확률
};

// 좀비 스폰 정보를 저장하는 구조체
USTRUCT(BlueprintType)
struct FZombieSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ANXNonPlayerCharacter> ZombieClass;  // 스폰할 좀비 클래스

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;  // 스폰 확률
};

UCLASS()
class NXPROJECT_API ANXSpawner : public AActor
{
    GENERATED_BODY()

public:
    ANXSpawner();

    // 랜덤 아이템 스폰
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomItem();

    // 랜덤 좀비 스폰
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomZombie();

protected:

    /** 공통 **/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    FVector GetRandomPointInVolume() const;

    /** 아이템 **/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    FItemSpawnRow* GetRandomItem() const;
    void SpawnItem(TSubclassOf<AActor> ItemClass);

    /** 좀비 **/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ZombieDataTable;

    FZombieSpawnRow* GetRandomZombie() const;
    void SpawnZombie(TSubclassOf<ANXNonPlayerCharacter> ZombieClass);
};
