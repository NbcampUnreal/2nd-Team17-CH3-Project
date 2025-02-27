//#include "Game/NXSpawner.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Engine/World.h"
//#include "Components/BoxComponent.h"
//
//ANXSpawner::ANXSpawner()
//{
//    PrimaryActorTick.bCanEverTick = false;
//
//    // 박스 컴포넌트 생성 후 루트 설정
//    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
//    SetRootComponent(Scene);
//
//    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
//    SpawningBox->SetupAttachment(Scene);
//}
//
//FVector ANXSpawner::GetRandomPointInVolume() const
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
//// 아이템 스폰 함수
//void ANXSpawner::SpawnItem(TSubclassOf<AActor> ItemClass)
//{
//    if (!ItemClass) return;
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
//    // 아이템 생성
//    AActor* SpawnedItem = World->SpawnActor<AActor>(ItemClass, SpawnLocation, FRotator::ZeroRotator);
//    if (!SpawnedItem)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn item!"));
//    }
//}
