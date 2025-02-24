#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NXZombieAIController.generated.h"

class UBlackboardData;
class UBehaviorTree;

UCLASS()
class NXPROJECT_API ANXZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANXZombieAIController();

	friend class ANXZombieCharacter;

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BeginAI(APawn* InPawn);

	void EndAI();

	/*
private:
	void OnPatrolTimerElapsed();

public:
	FTimerHandle PatrolTimerHandle = FTimerHandle();

	static const float PatrolRepeatInterval;

	static const float PatrolRadius;
	*/

public:
	static const float PatrolRadius;

	static int32 ShowAIDebug;

	static const FName StartPatrolPositionKey;

	static const FName EndPatrolPositionKey;

	static const FName TargetCharacterKey;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBlackboardData> BlackboardDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTree> BehaviorTree;

};