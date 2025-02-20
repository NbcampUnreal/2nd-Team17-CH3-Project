#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NXItemInterface.h"
#include "NXBaseItem.generated.h"

UCLASS()
class NXPROJECT_API ANXBaseItem : public AActor, public INXItemInterface
{
	GENERATED_BODY()
	
public:	
	ANXBaseItem();

protected:
		//액터에 진입했을 때(오버랩)
		virtual void OnItemOverlap(AActor* OverlapActor) override;
		//액터 진입 이후(오버랩 이후)
		virtual void OnItemEndOverlap(AActor* OverlapActor) override;
		//아이템 사용
		virtual void ActivateItem(AActor* Activator) override;
		//아이템 이름으로 구분하여 사용
		virtual FName GetItemType() const override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FName ItemType;
};
