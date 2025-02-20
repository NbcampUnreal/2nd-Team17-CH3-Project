#pragma once

#include "CoreMinimal.h"
#include "Item/NXBaseItem.h"
#include "NXBulletItem.generated.h"

UCLASS()
class NXPROJECT_API ANXBulletItem : public ANXBaseItem
{
	GENERATED_BODY()
	
public:
    ANXBulletItem();  // 생성자 선언

    // 에디터에서 총알 수정가능
    // 아이템 사용할 때 BulletCount만큼 충전
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 BulletCount;
};
