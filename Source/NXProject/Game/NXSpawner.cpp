#include "Game/NXSpawner.h"
#include "AI/NXNonPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Game/WaveData.h"
#include "Components/BoxComponent.h"

// ������
ANXSpawner::ANXSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    // Scene ��Ʈ ����
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    // SpawningBox ����
    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);
}

// ������ �ڽ� ���ο��� ���� ��ġ ��ȯ
FVector ANXSpawner::GetRandomPointInVolume() const
{
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

/** ������ ���� �Լ� **/

void ANXSpawner::SpawnRandomItem()
{
    if (FItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            SpawnItem(ActualClass);
        }
    }
}

FItemSpawnRow* ANXSpawner::GetRandomItem() const
{
    if (!ItemDataTable) return nullptr;

    // 1) ��� Row(��) ��������
    TArray<FItemSpawnRow*> AllRows;
    static const FString ContextString(TEXT("ItemSpawnContext"));
    ItemDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    // 2) Ȯ�� ��� ���� ����
    float TotalChance = 0.0f;
    for (const FItemSpawnRow* Row : AllRows)
    {
        if (Row) TotalChance += Row->SpawnChance;
    }

    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumulateChance = 0.0f;

    for (FItemSpawnRow* Row : AllRows)
    {
        AccumulateChance += Row->SpawnChance;
        if (RandValue <= AccumulateChance)
        {
            return Row;
        }
    }

    return nullptr;
}



void ANXSpawner::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass) return;

    UWorld* World = GetWorld();
    if (!World) return;

    FVector SpawnLocation = GetRandomPointInVolume();
    World->SpawnActor<AActor>(ItemClass, SpawnLocation, FRotator::ZeroRotator);
}

/** ���� ���� �Լ� **/

void ANXSpawner::SpawnRandomZombie()
{
    if (FZombieSpawnRow* SelectedRow = GetRandomZombie())
    {
        if (SelectedRow->ZombieClass)
        {
            SpawnZombie(SelectedRow->ZombieClass); // �ٷ� ����
        }
    }
}


FZombieSpawnRow* ANXSpawner::GetRandomZombie() const
{
    if (!ZombieDataTable) return nullptr;

    // 1) ��� Row ��������
    TArray<FZombieSpawnRow*> AllRows;
    static const FString ContextString(TEXT("ZombieSpawnContext"));
    ZombieDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    // 2) Ȯ�� ��� ���� ����
    float TotalChance = 0.0f;
    for (const FZombieSpawnRow* Row : AllRows)
    {
        if (Row) TotalChance += Row->SpawnChance;
    }

    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumulateChance = 0.0f;

    for (FZombieSpawnRow* Row : AllRows)
    {
        AccumulateChance += Row->SpawnChance;
        if (RandValue <= AccumulateChance)
        {
            return Row;
        }
    }

    return nullptr;
}

void ANXSpawner::SpawnZombie(TSubclassOf<ANXNonPlayerCharacter> ZombieClass)
{
    if (!ZombieClass) return;

    UWorld* World = GetWorld();
    if (!World) return;

    FVector SpawnLocation = GetRandomPointInVolume();
    World->SpawnActor<ANXNonPlayerCharacter>(ZombieClass, SpawnLocation, FRotator::ZeroRotator);
}
