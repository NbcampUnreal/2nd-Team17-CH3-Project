#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "NXZombieCharacter.generated.h"


UCLASS()
class NXPROJECT_API ANXZombieCharacter : public ANXCharacterBase
{
	GENERATED_BODY()
	
public:
	ANXZombieCharacter();

	virtual void BeginPlay() override;

};
