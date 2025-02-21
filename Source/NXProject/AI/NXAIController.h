
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
	float StopMoveTime;

	FTimerHandle MoveTimerHandle;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	/*virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void RandomMove();*/
};
