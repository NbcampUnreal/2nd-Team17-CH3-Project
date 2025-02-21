
#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "NXNonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API ANXNonPlayerCharacter : public ANXCharacterBase
{
	GENERATED_BODY()
	
public:
	ANXNonPlayerCharacter();
	UPROPERTY()
	float WalkSpeed;
	float RunSpeed;
};
