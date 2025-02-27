#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NXItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNXItemInterface : public UInterface
{
	GENERATED_BODY()
};

class NXPROJECT_API INXItemInterface
{
	GENERATED_BODY()

public:
	// 아이템을 오버랩했을 때 호출되는 함수
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;

	// 액터 진입 이후(오버랩 이후)
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	// 아이템 사용
	virtual void ActivateItem(AActor* Activator) = 0;

	// 아이템 이름으로 구분하여 사용
	virtual FName GetItemType() const = 0;
};
