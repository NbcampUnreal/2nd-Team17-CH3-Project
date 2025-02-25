
#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "GameFramework/Character.h"
#include "NXNonPlayerCharacter.generated.h"

class UWidgetComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;
	void UpdateOverheadHP();
protected:
	
	virtual void OnDeath()override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};