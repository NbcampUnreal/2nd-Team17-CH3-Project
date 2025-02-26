#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SUIPlayerController.generated.h"

UCLASS()
class NXPROJECT_API ASUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** ������ ���۵� �� ȣ��Ǵ� �Լ� */
	virtual void BeginPlay() override;

private:
	/** UI ������ Ŭ������ �����ϴ� ���� (�������Ʈ���� ���� ����) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ASUIPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> UIWidgetClass;

	/** ���� ������ UI ���� �ν��Ͻ� */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ASUIPlayerController, Meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> UIWidgetInstance;

};