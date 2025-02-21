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

	// ��������Ʈ �߰�
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCheckHitDelegate OnCheckHit;

	// ���� �ִϸ��̼� ���� �� Ư�� Ÿ�ֿ̹� ȣ��� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void NotifyCheckHit();
};