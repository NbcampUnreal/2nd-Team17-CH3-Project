// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NXNPCAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckHit);

UCLASS()
class NXPROJECT_API UNXNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void AnimNotify_CheckHit();

public:
	FOnCheckHit OnCheckHit;
};
