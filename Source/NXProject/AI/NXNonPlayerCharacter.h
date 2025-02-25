
#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "GameFramework/Character.h"
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

	virtual void BeginPlay() override;

protected:

};