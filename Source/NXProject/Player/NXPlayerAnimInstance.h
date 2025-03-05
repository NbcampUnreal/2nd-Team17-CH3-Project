// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NXPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API UNXPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void AnimNotify_AN_FootPlant_Left();
	UFUNCTION()
	void AnimNotify_AN_FootPlant_Right();
};
