#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"  // ������ ���̺��� ����Ϸ��� �ʿ���
#include "WaveData.generated.h"


class ARandomSpawner;

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_BODY()

    // ������ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemName;
    // � ������ Ŭ������ ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;


    //���� Ȯ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;


    //�������
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ZombieName;
    // � ������ Ŭ������ ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ZombieClass;
};

//������ ���̺� �������
