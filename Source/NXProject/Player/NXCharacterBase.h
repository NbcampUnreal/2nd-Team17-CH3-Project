#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NXCharacterBase.generated.h"



UCLASS()
class NXPROJECT_API ANXCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANXCharacterBase();

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddHealth(float Amount);

protected:

	


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
