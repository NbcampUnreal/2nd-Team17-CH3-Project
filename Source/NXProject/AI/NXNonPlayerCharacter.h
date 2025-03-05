
#pragma once
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* HittedEffect;


	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;


	// 엔딩 UI 클래스
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LoseScreenClass; // WBP_LoseScreen

	void UpdateOverheadHP();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();
	void EnableRagdoll();
	
	bool bIsPlayedEffect;
	void EndPlayedEffect();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
private:
	bool bIsDead;
	// 위젯 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* OverheadWidget;

};