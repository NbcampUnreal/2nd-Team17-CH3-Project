#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NXZombieAnimInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckHitDelegate);

UCLASS()
class NXPROJECT_API UNXZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNXZombieAnimInstance();

	// 델리게이트 추가
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCheckHitDelegate OnCheckHit;

	// 공격 애니메이션 실행 중 특정 타이밍에 호출될 함수
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void NotifyCheckHit();
};