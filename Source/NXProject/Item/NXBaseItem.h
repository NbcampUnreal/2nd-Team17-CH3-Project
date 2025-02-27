#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NXItemInterface.h"
#include "NXBaseItem.generated.h"

class USphereComponent; 

UCLASS()
class NXPROJECT_API ANXBaseItem : public AActor, public INXItemInterface //인터페이스 상속
{
	GENERATED_BODY()
	
public:	
	ANXBaseItem();

protected:

	virtual void BeginPlay() override;

	//컴포넌트별 리플렉션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")
	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;


	//액터에 진입했을 때(오버랩)
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	//액터 진입 이후(오버랩 이후)
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	//아이템 사용
	virtual void ActivateItem(AActor* Activator) override;
	//아이템 이름으로 구분하여 사용
	virtual FName GetItemType() const override;

	void DestroyItem(); //함수를 통해 사라지기(그 함수는 오버랩)
};
