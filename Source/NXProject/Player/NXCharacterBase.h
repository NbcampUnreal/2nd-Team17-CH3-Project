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

	UFUNCTION(BlueprintPure, Category = "Health")
	virtual int32 GetHealth() const; //현재 체력을 가져오는 함수.
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddHealth(float Amount);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth; //최대 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health; //현재 체력
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath(); // 사망 처리 함수 (체력 0 이하 호출)



public:
	virtual void Attack();
	//데미지 처리 함수
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

};
