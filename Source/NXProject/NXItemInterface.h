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
	//액터에 진입했을 때(오버랩)
	virtual void OnItemOverlap(AActor* OverlapActor) = 0; 
	//액터 진입 이후(오버랩 이후)
	virtual void OnItemEndOverlap(AActor* OverlapActor) = 0;
	//아이템 사용
	virtual void ActivateItem(AActor* Activator) = 0;
	//아이템 이름으로 구분하여 사용
	virtual FName GetItemType() const = 0;
};
