
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NXAIController.generated.h"

/**
 * 
 */
UCLASS()
class NXPROJECT_API ANXAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBlackboardData> BlackboardDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	void BeginAI(APawn* InPawn);

	void EndAI();

};
