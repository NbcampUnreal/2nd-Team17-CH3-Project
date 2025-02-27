
#pragma once

#include "CoreMinimal.h"
#include "Player/NXCharacterBase.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UAnimMontage* NPCDeadAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* NPCHittedAnimation;

	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	void UpdateOverheadHP();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
private:
	bool bIsDead;
};