
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
	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;
	void UpdateOverheadHP();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};