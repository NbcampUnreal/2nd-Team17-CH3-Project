#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  // 데이터 테이블을 사용하려면 필요함
#include "WaveData.generated.h"


class ARandomSpawner;

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_BODY()

    // 아이템 버전
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemName;
    // 어떤 아이템 클래스를 스폰할지
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;


    //스폰 확률
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;


    //좀비버전
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ZombieName;
    // 어떤 아이템 클래스를 스폰할지
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ZombieClass;
};

//데이터 테이블 구성요소
