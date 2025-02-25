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
	virtual int32 GetHealth() const; //���� ü���� �������� �Լ�.
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddHealth(float Amount);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth; //�ִ� ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health; //���� ü��
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath(); // ��� ó�� �Լ� (ü�� 0 ���� ȣ��)



public:
	virtual void Attack();
	//������ ó�� �Լ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

};
