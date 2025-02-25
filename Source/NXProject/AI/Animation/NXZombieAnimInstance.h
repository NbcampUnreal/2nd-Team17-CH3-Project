#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NXZombieAnimInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZombieCheckHitDelegate);

UCLASS()
class NXPROJECT_API UNXZombieAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UNXZombieAnimInstance();

    UPROPERTY(BlueprintAssignable, Category = "Event")
    FOnZombieCheckHitDelegate OnCheckHit;

    // ???? ??????? ???? ?? ??? ????? ???? ???
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void NotifyCheckHit();
};
