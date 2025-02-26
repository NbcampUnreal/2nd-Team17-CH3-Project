#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/SUIPlayerController.h"
#include "SUIPlayerController_Loading.generated.h"


UCLASS()
class NXPROJECT_API ASUIPlayerController_Loading : public ASUIPlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

};
