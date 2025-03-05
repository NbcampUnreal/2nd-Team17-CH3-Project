#pragma once
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "CoreMinimal.h"
#include "Item/NXBaseItem.h"
#include "NXBigHealItem.generated.h"


UCLASS()
class NXPROJECT_API ANXBigHealItem : public ANXBaseItem
{
	GENERATED_BODY()

public:
    ANXBigHealItem();

    UPROPERTY(EditAnywhere, Category = "Item")
    float HealAmount; //회복량 블루프린트에서 수정가능

    UFUNCTION(BlueprintCallable, Category = "Item")
    float GetHealAmount() const { return HealAmount; }

    UFUNCTION(BlueprintCallable, Category = "Item")
    void SetHealAmount(float NewHealAmount) { HealAmount = NewHealAmount; }

    virtual void ActivateItem(AActor* Activator) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
    UNiagaraSystem* HealingEffect;
};
