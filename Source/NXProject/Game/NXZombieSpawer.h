//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "Components/BoxComponent.h"  //  추가
//#include "NXZombieSpawer.generated.h"
//
//class ANXNonPlayerCharacter;
//class UBoxComponent;
//class ARandomSpawner;
//
//UCLASS()
//class NXPROJECT_API ANXZombieSpawer : public AActor
//{
//	GENERATED_BODY()
//	
//public:
//    ANXZombieSpawer();
//
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
//    USceneComponent* Scene;
//
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
//    UBoxComponent* SpawningBox;
//
//    UFUNCTION(BlueprintCallable, Category = "Spawning")
//    FVector GetRandomPointInVolume() const;
//
//    // 좀비 스폰 함수 선언
//    UFUNCTION(BlueprintCallable, Category = "Spawning")
//    void SpawnZombie(TSubclassOf<ANXNonPlayerCharacter> ZombieClass);
//};
