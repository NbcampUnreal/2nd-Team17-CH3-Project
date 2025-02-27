//#include "Game/NXZombieSpawer.h"
//#include "AI/NXNonPlayerCharacter.h"
//#include "Components/BoxComponent.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Engine/World.h"
//
//ANXZombieSpawer::ANXZombieSpawer()
//{
//    PrimaryActorTick.bCanEverTick = true;
//
//    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
//    SetRootComponent(Scene);
//
//    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
//    SpawningBox->SetupAttachment(Scene);
//}
//
//// ���� �ڽ� ���� ���� ��ġ ��������
//FVector ANXZombieSpawer::GetRandomPointInVolume() const
//{
//    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
//    FVector BoxOrigin = SpawningBox->GetComponentLocation();
//
//    return BoxOrigin + FVector(
//        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
//        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
//        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
//    );
//}
//
//// ���� ���� �Լ�
//void ANXZombieSpawer::SpawnZombie(TSubclassOf<ANXNonPlayerCharacter> ZombieClass)
//{
//    if (!ZombieClass) return;
//
//    UWorld* World = GetWorld();
//    if (!World)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("GetWorld() returned nullptr!"));
//        return;
//    }
//
//    FVector SpawnLocation = GetRandomPointInVolume();
//    if (SpawnLocation == FVector::ZeroVector)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Invalid spawn location!"));
//        return;
//    }
//
//    ANXNonPlayerCharacter* SpawnedZombie = World->SpawnActor<ANXNonPlayerCharacter>(ZombieClass, SpawnLocation, FRotator::ZeroRotator);
//    if (!SpawnedZombie)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn zombie!"));
//    }
//}
