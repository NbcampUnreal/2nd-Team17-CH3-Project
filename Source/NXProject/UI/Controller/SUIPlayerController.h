#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SUIPlayerController.generated.h"

UCLASS()
class NXPROJECT_API ASUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** 게임이 시작될 때 호출되는 함수 */
	virtual void BeginPlay() override;

private:
	/** UI 위젯의 클래스를 설정하는 변수 (블루프린트에서 설정 가능) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ASUIPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> UIWidgetClass;

	/** 현재 생성된 UI 위젯 인스턴스 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ASUIPlayerController, Meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> UIWidgetInstance;

};